--Global settings
Global  =  {}
--�Ⱞ骨 䰠겠렍
SerpinFractalSetings = {}

--⮪孻
TK_L=0	
TK_A=1
TK_B=2
--譨樠먧ඨࠪ⠫࠱尯譱ꮣ
function BuildSerpinFractal()
	--Რಮ⻩ ﮲
	SerpinFractalSetings.startStream=Fractal.createFractalStream(TK_L,TK_B,TK_L,TK_B,TK_L)
	if SerpinFractalSetings.startStream == nil then
		return false
	end
	--﮲砬孻
	SerpinFractalSetings.replaceStream1=Fractal.createFractalStream(TK_L,TK_A,TK_L,TK_B,TK_L,TK_A,TK_L)	
	if SerpinFractalSetings.replaceStream1 == nil then
		return false
	end
	--ᮧ䠥젣렢� 媲 尠�蹠 ﮲⠲�
	SerpinFractalSetings.state=Fractal.createFractalState(SerpinFractalSetings.startStream)	
	if SerpinFractalSetings.state == nil then
		return false
	end
	--㱲ୠ⫨⠥젲�ଥ�蠯꠭ࠪ໩ ᳤岠砬孥퍊	
	if Fractal.setReplaceTockenData(SerpinFractalSetings.state,TK_L,SerpinFractalSetings.replaceStream1) ==false then
		return false
	end
	return true
end
--ﰨ쥭塞 ।� ⮪孨਱㥬/觬孿嬠᮱⮿�)
function fractaltockenSet( StateV, tocken)
	if tocken==TK_L then
	   GL.Colord(0.0,0.0,1.0)
	   GL.Vertex(StateV.x, StateV.y)
		StateV.x=StateV.x+math.cos(StateV.a)*StateV.r
		StateV.y=StateV.y+math.sin(StateV.a)*StateV.r
	   GL.Colord(1.0,1.0,1.0)
	   GL.Vertex(StateV.x, StateV.y)	
	elseif  tocken==TK_A then
		StateV.a=StateV.a+StateV.da1
	elseif  tocken==TK_B then
		StateV.a=StateV.a-StateV.da2
	end
	return StateV
end
function fractalDraw(fs )
 if fs.lockator ~=nil then
 
	if Mutex.tryLock(fs.lockator,WND.INFINITE) then
		
		fs.StateV={}
		fs.StateV.x=fs.startX;
		fs.StateV.y=fs.startY;
		fs.StateV.a=fs.startA;
		fs.StateV.r=fs.startR;
		fs.StateV.da1=SerpinFractalSetings.da2
		fs.StateV.da2=SerpinFractalSetings.da1
		
		Fractal.stream_reset(fs.state)
	GL.Begin(GL.LINES)
		while Fractal.stream_eos(fs.state) == false do
			local res, tocken=Fractal.stream_get(fs.state)
			if res then
				fs.StateV=fractaltockenSet(fs.StateV,tocken)
			end
		end
	GL.End()
		Mutex.Release(fs.lockator)
	end
  end
end
function fractalMutante( fs,i)
 if fs.lockator ~=nil then
 
	if Mutex.tryLock(fs.lockator,WND.INFINITE) then
		
		Fractal.newLevel(fs.state)
		SerpinFractalSetings.startR=SerpinFractalSetings.startR*SerpinFractalSetings.dr
		
		print(i)
		Mutex.Release(fs.lockator)
	end
  end
end

function initialize()
	Global.drawMutex=Mutex.Create('luaMutexDrawGL')
	Global.mainWindow=nil
	--
	SerpinFractalSetings.lockator=Mutex.Create()
	SerpinFractalSetings.startStream=nil
	SerpinFractalSetings.replaceStream1=nil
	SerpinFractalSetings.state=nil
	---------------------------------
	SerpinFractalSetings.startX=0.0
	SerpinFractalSetings.startY=0.0
	SerpinFractalSetings.startA=0.0
	SerpinFractalSetings.startR=3.0
	SerpinFractalSetings.da1=(math.pi*2.0)/3.0
	SerpinFractalSetings.da2=(math.pi)/3.0
	SerpinFractalSetings.dr=1.0/3.0
	---------------------------------
	if BuildSerpinFractal()  == false  then
		return false
	end
	return true
end
function main()
	if initialize() == false then
		return
	end
	Global.mainWindow=WND.initWindow('draw()',800,700)
	
	
	for i=1,15 do
		WND.Sleep(1000);
		
		fractalMutante(SerpinFractalSetings,i);

	end
	--------------------------------------------------------
	WND.waitForCloseWindow(Global.mainWindow,WND.INFINITE)
	Mutex.Destroy(Global.drawMutex);
	Global.drawMutex=nil
end
function draw()
	if Mutex.tryLock(Global.drawMutex,WND.INFINITE) then
		GL.Translate(-1.5,1.0,-6.0)
		
		fractalDraw(SerpinFractalSetings)
		
		Mutex.Release(Global.drawMutex)
	end
end
main();