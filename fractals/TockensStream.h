#pragma once
#include <map>
#include <stack>
namespace fractal
{
	using TockenType = unsigned char;
	struct TockensStreamData
	{
		TockenType* stream		= nullptr;
		int			streamSize	= 0;
	};
	//-----------------------------------------------------------------------
	class TockensStream
	{
	private:
		TockensStreamData*	_stream_data_ptr;
		int					_pos;
	protected:
		//закрытый интерфейс управления потоком
		//для упрощения написания кода в наследниках
		TockensStreamData* _getStreamDataPtr() const;
		const TockenType&  _getNextTocken();
		const TockenType&  _peekNextTocken() const;
		bool               _eos() const;
		void               _reset();
	public:
		//открытый интерфейс управления потоком
		                          TockensStream(TockensStreamData* data_ptr, int startPos = 0);
		virtual const TockenType &getNextTocken();
		virtual const TockenType &peekNextTocken() const;
		virtual bool              eos() const;
		virtual void              reset();

		static bool               createStream(TockensStreamData *data_ptr, int streaSize);
		static bool               setTocken(TockensStreamData *data_ptr, int position, TockenType t);
		static bool               freeStream(TockensStreamData *data_ptr);
	};
	//-----------------------------------------------------------------------
	using TockenReplace = std::pair<TockenType, TockensStreamData*>;
	//-----------------------------------------------------------------------
	class FractalSystemState :
		public TockensStream
	{
	public:
		using TockenReplaceTableType = std::map<TockenType, TockensStreamData*>;
		using RecursiveFractalStackType = std::stack<TockensStream>;
	private:
		TockenReplaceTableType		_tockenReplaceTable;
		int							_fractalLevel;

		RecursiveFractalStackType	_recursiveFractalStack;
	protected:
		int                recursiveFractalStackLevel() const;
		const TockenType& _peekNextTockenInStack() const;
		void clearRecursizeStack();
	public:
		                   FractalSystemState(TockensStreamData* data_ptr, int startPos = 0);
		void               setReplaceTockenData(TockenType t, TockensStreamData *data_ptr);

		virtual const TockenType &getNextTocken()        override;
		virtual const TockenType &peekNextTocken() const override;
		virtual bool              eos() const            override;
		virtual void              reset()                override;
		void                      newFractalLevel();
	};
}
using Fr_tockenT	= fractal::TockenType;
using Fr_streamT	= fractal::TockensStreamData;
using Fr_tckStreamT = fractal::TockensStream;
using Fr_stateT		= fractal::FractalSystemState;

bool initFractalStream(Fr_streamT* stream, int size);
bool freeStream(Fr_streamT* stream);
bool setFractalStreamTocken(Fr_streamT* stream, int position, Fr_tockenT t);
bool createFractalStream(Fr_streamT* stream, Fr_tockenT* tockens, int size);
