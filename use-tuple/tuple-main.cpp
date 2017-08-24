#include<tuple>
#include<iostream>

// helper function to tuple_each a tuple of any size
template<class Tuple, typename Func, std::size_t N>
struct TupleEach {
	static void tuple_each(Tuple& t, Func& f)
	{
		TupleEach<Tuple, Func, N - 1>::tuple_each(t, f);
		f(std::get<N - 1>(t));
	}
};

template<class Tuple, typename Func>
struct TupleEach<Tuple, Func, 1> {
	static void tuple_each(Tuple& t, Func& f)
	{
		f(std::get<0>(t));
	}
};

template<typename Tuple, typename Func>
void tuple_each(Tuple& t, Func& f)
{
	TupleEach<Tuple, Func, std::tuple_size<Tuple>::value>::tuple_each(t, f);
}
// end helper function




int main()
{

	auto tup = std::tuple<double, short, int, long long, double>(0, 10, 200, 3000, 400.01);

	tuple_each(tup, [](auto& v) {std::cout << "sizeof(v)" << sizeof(v) << ' '; });
	std::cout << std::endl;
	tuple_each(tup, [](auto& v) {std::cout << "address(v)" << &v << ' '; });
	std::cout << std::endl;

	tuple_each(tup, [](auto& v) {v += 1; });
	tuple_each(tup, [](auto& v) {std::cout << v << ' '; });

}
