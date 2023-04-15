#pragma once

template<class RET, class ... ARG>
class Mother{
public:
  using Parent = Mother<RET, ARG...>;
  Mother(ARG...arg)
    :data_(make_tuple(arg...))
  {}

  template<class TARGET>
  Mother w(TARGET const &d) const
  {
    auto ret = *this;
    std::get<TARGET>(ret.data_) = d;
    return ret;
  }
      
  operator RET () const
  {return get();}

  RET get () const
  {
    return make_from_tuple<RET>(data_);
  }
private:
    tuple<ARG...> data_;
};
