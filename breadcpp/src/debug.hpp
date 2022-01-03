
#ifdef _MSC_VER 
#ifdef _DEBUG
#define BREAD_DEBUG_MODE true;
#else
#define BREAD_DEBUG_MODE false;
#endif
#else
#ifdef NDEBUG
#define BREAD_DEBUG_MODE false;
#endif
#endif // !BREAD_DEBUG_MODE


constexpr bool is_debug() {
#ifdef NDEBUG
	return false;
#else
	return true;
#endif // DEBUG

}