#pragma once


class WindowSplitter
{
public:
	CSplitterWnd m_main_splitter;
	CFrameWnd* m_frame;
	bool is_initialized;
public:
	WindowSplitter(CFrameWnd* frame) :m_frame(frame), is_initialized(0) {}
	bool init_static() {
		if (!m_main_splitter.CreateStatic(m_frame, 1, 2)) return false;
		return true;
	}
	bool init_view(int col_idx, CSize size, CRuntimeClass* view_class, CCreateContext* pContext) {
		bool view_created = m_main_splitter.CreateView(0, col_idx, view_class, size, pContext);
		return view_created;
	}
	bool is_ready() const { return is_initialized; }
};

