#ifndef _UndoStack_UndoStack_h_
#define _UndoStack_UndoStack_h_

#include <Core/Core.h>

namespace Upp
{
	
	class UndoStackData : Moveable<UndoStackData> {
		public:
		Callback undoAction;
		Callback redoAction;
	
		void Merge(const UndoStackData& mostRecentAction) {
			// x === A==> y === B==> z        x ==> C==> z    C =  A >> B
			// x <==~A=== y <==~B=== z        x <==~C<== z   ~C = ~B >> ~A
			Callback cb;
			(cb << mostRecentAction.undoAction) << undoAction;
			undoAction = cb;
			
			cb.Clear();
			(cb << redoAction) << mostRecentAction.redoAction;
			redoAction = cb;
		}
	};
	
	
	class UndoStack {
		public:
			
		private:
			Vector<UndoStackData> _undoStack;
			Vector<UndoStackData> _redoStack;
			int64 _lastActionAddTime;
			int _undoStackSize;
			
			void trimStack() {
				if ( _undoStack.GetCount() > _undoStackSize) {
					_undoStack.Remove(0, _undoStack.GetCount() - _undoStackSize);
				}
			}
		public:
			UndoStack() : _lastActionAddTime(0), _undoStackSize(100) {}
			
			void SetUndoStackSize(unsigned int p) {
				_undoStackSize = p;
				trimStack();
			}
			bool CanUndo() const { return !_undoStack.IsEmpty(); }
			bool CanRedo() const  { return !_redoStack.IsEmpty(); }
			
			void AddUndoAction(UndoStackData& CB) {
				int64 currTime = GetTickCount();
				if ((currTime - _lastActionAddTime) < 500) _undoStack.Top().Merge(CB);
				else                                       _undoStack.Add(CB);
				_redoStack.Clear();
				_lastActionAddTime = currTime;
				trimStack();
			}
	
			bool Undo() {
				if ( !_undoStack.IsEmpty() ) {
					UndoStackData cb = _undoStack.Pop();
					_redoStack.Add(cb);
					cb.undoAction();
					return true;
				}
				return false;
			}
			
			bool Redo() {
				if ( !_redoStack.IsEmpty() ) {
					UndoStackData cb = _redoStack.Pop();
					_undoStack.Add(cb);
					cb.redoAction();
					return true;
				}
				return false;
			}
	};
}

#endif
