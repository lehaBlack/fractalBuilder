#include "..\fractals\TockensStream.h"
#include <exception>
//TockensStream-----------------------------------------------------------------
fractal::TockensStream::TockensStream(TockensStreamData * data_ptr, int startPos):
	_stream_data_ptr(data_ptr),
	_pos(startPos)
{
}
const fractal::TockenType& fractal::TockensStream::getNextTocken()
{
	return _getNextTocken();
}
const fractal::TockenType& fractal::TockensStream::peekNextTocken() const
{
	return _peekNextTocken();
}
bool fractal::TockensStream::eos() const
{
	return _eos();
}
void fractal::TockensStream::reset()
{
	return _reset();
}
fractal::TockensStreamData * fractal::TockensStream::_getStreamDataPtr() const
{
	return _stream_data_ptr;
}
const fractal::TockenType& fractal::TockensStream::_getNextTocken()
{
	const TockenType &t = _peekNextTocken();
	_pos++;
	return t;
}
const fractal::TockenType& fractal::TockensStream::_peekNextTocken() const
{
	if (_stream_data_ptr->streamSize <= _pos)
		throw std::exception("out of memory proc:" __FUNCTION__);
	return _stream_data_ptr->stream[_pos];
}
bool fractal::TockensStream::_eos() const
{
	return _stream_data_ptr->streamSize == _pos;
}
void fractal::TockensStream::_reset()
{
	_pos = 0;
}
bool fractal::TockensStream::createStream(TockensStreamData * data_ptr, int streaSize)
{
	data_ptr->stream = new TockenType[streaSize];
	data_ptr->streamSize = streaSize;
	return true;
}

bool fractal::TockensStream::setTocken(TockensStreamData * data_ptr, int position, TockenType t)
{
	if (data_ptr->streamSize <= position)
		throw std::exception("out of memory proc:" __FUNCTION__);
	data_ptr->stream[position] = t;
	return true;
}
bool fractal::TockensStream::freeStream(TockensStreamData * data_ptr)
{
	if (data_ptr->stream != nullptr)
		delete[] data_ptr->stream;
	data_ptr->stream = nullptr;
	data_ptr->streamSize = 0;
	return true;
}
//FractalSystemState-----------------------------------------------------------------
int fractal::FractalSystemState::recursiveFractalStackLevel() const
{
	return _recursiveFractalStack.size();
}
const fractal::TockenType& fractal::FractalSystemState::_peekNextTockenInStack() const
{
	return _recursiveFractalStack.top().peekNextTocken();
}
void fractal::FractalSystemState::clearRecursizeStack()
{
	int newLevel = recursiveFractalStackLevel();

	if (newLevel > 0)
	{
		while (newLevel<_fractalLevel)
		{
			TockenType t = _recursiveFractalStack.top().peekNextTocken();
			if (_tockenReplaceTable.count(t) == 0)
				break;
			TockensStreamData* data_ptr = _tockenReplaceTable[t];
			_recursiveFractalStack.push(TockensStream(data_ptr));
			newLevel = recursiveFractalStackLevel();
		}
	}
}
fractal::FractalSystemState::FractalSystemState(TockensStreamData* data_ptr, int startPos):
	TockensStream(data_ptr, startPos),
	_tockenReplaceTable(),
	_fractalLevel(1),
	_recursiveFractalStack()
{
	reset();
}

void fractal::FractalSystemState::setReplaceTockenData(TockenType t, TockensStreamData* data_ptr)
{
	_tockenReplaceTable.insert(TockenReplace( t, data_ptr ));
}

const fractal::TockenType& fractal::FractalSystemState::getNextTocken()
{
	const TockenType& r = peekNextTocken();
	bool eos = false;
	do
	{
		//переходим к следующему состоянию
		_recursiveFractalStack.top().getNextTocken();
		eos = _recursiveFractalStack.top().eos();
		if (eos)
			_recursiveFractalStack.pop();
	} while (eos && recursiveFractalStackLevel() > 0);

	clearRecursizeStack();
	return r;
}

const fractal::TockenType& fractal::FractalSystemState::peekNextTocken() const
{
	int level = recursiveFractalStackLevel();
	if(level==0)
		throw std::exception("fractal replace stack is clear proc:" __FUNCTION__);
	return _peekNextTockenInStack();
}

bool fractal::FractalSystemState::eos() const
{
	return recursiveFractalStackLevel()==0;
}

void fractal::FractalSystemState::reset()
{
	while (_recursiveFractalStack.size() > 0)
		_recursiveFractalStack.pop();
	_recursiveFractalStack.push(TockensStream(_getStreamDataPtr()));
	clearRecursizeStack();
}

void fractal::FractalSystemState::newFractalLevel()
{
	_fractalLevel++;
	reset();
}

bool initFractalStream(Fr_streamT * stream, int size)
{
	return fractal::TockensStream::createStream(stream, size);
}

bool freeStream(Fr_streamT * stream)
{
	return fractal::TockensStream::freeStream(stream);
}

bool setFractalStreamTocken(Fr_streamT * stream, int position, Fr_tockenT t)
{
	return fractal::TockensStream::setTocken(stream, position, t);
}

bool createFractalStream(Fr_streamT * stream, Fr_tockenT * tockens, int size)
{
	bool init = initFractalStream(stream, size);
	if (!init)
		return false;
	for (int i = 0; i < size; i++)
	{
		bool set = setFractalStreamTocken(stream, i, tockens[i]);
		if (!set)
			return false;
	}
	return true;
}
