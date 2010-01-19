#ifndef RANGE_HPP
#define RANGE_HPP

template<typename T>
class Range {
	public:
		Range(T start, T end) : _start(start), _end(end) {}
		
		bool include(const T& e)
		{
			return (e >= _start && e <= _end);
		}
	private:
		T _start;
		T _end;
};

#endif

