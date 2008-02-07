#include <algorithm>
#include <functional>
template <typename ReturnType, typename CalleeType, typename ArgType>
    class other_mem_fun_t
{
    typedef ReturnType (CalleeType::*function_t) (ArgType);
    CalleeType *m_callee;
    function_t m_pfn;

public:
    other_mem_fun_t(CalleeType *callee, function_t pfn)
        : m_callee(callee), m_pfn(pfn)
	{
	}

    ReturnType operator() (ArgType arg) const
    {
        return (m_callee->*m_pfn)(arg);
    }
};

template <typename ReturnType, typename CalleeType, typename ArgType>
other_mem_fun_t<ReturnType, CalleeType, ArgType>
    other_mem_fun(CalleeType *callee, ReturnType (CalleeType::* pfn)(ArgType))
{
    return other_mem_fun_t<ReturnType, CalleeType, ArgType>(callee, pfn);
}
