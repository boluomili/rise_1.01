// Generated by gencpp from file unitree_guide/publish_rise.msg
// DO NOT EDIT!


#ifndef UNITREE_GUIDE_MESSAGE_PUBLISH_RISE_H
#define UNITREE_GUIDE_MESSAGE_PUBLISH_RISE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace unitree_guide
{
template <class ContainerAllocator>
struct publish_rise_
{
  typedef publish_rise_<ContainerAllocator> Type;

  publish_rise_()
    : posError()
    , velError()
    , Error2()
    , Error2_0()
    , intergral()
    , miu_t()
    , templesgn()
    , templemiu()
    , data1(0.0)
    , data2(0.0)
    , data3(0.0)
    , data4(0.0)  {
      posError.assign(0.0);

      velError.assign(0.0);

      Error2.assign(0.0);

      Error2_0.assign(0.0);

      intergral.assign(0.0);

      miu_t.assign(0.0);

      templesgn.assign(0.0);

      templemiu.assign(0.0);
  }
  publish_rise_(const ContainerAllocator& _alloc)
    : posError()
    , velError()
    , Error2()
    , Error2_0()
    , intergral()
    , miu_t()
    , templesgn()
    , templemiu()
    , data1(0.0)
    , data2(0.0)
    , data3(0.0)
    , data4(0.0)  {
  (void)_alloc;
      posError.assign(0.0);

      velError.assign(0.0);

      Error2.assign(0.0);

      Error2_0.assign(0.0);

      intergral.assign(0.0);

      miu_t.assign(0.0);

      templesgn.assign(0.0);

      templemiu.assign(0.0);
  }



   typedef boost::array<double, 3>  _posError_type;
  _posError_type posError;

   typedef boost::array<double, 3>  _velError_type;
  _velError_type velError;

   typedef boost::array<double, 3>  _Error2_type;
  _Error2_type Error2;

   typedef boost::array<double, 3>  _Error2_0_type;
  _Error2_0_type Error2_0;

   typedef boost::array<double, 3>  _intergral_type;
  _intergral_type intergral;

   typedef boost::array<double, 3>  _miu_t_type;
  _miu_t_type miu_t;

   typedef boost::array<double, 3>  _templesgn_type;
  _templesgn_type templesgn;

   typedef boost::array<double, 3>  _templemiu_type;
  _templemiu_type templemiu;

   typedef double _data1_type;
  _data1_type data1;

   typedef double _data2_type;
  _data2_type data2;

   typedef double _data3_type;
  _data3_type data3;

   typedef double _data4_type;
  _data4_type data4;





  typedef boost::shared_ptr< ::unitree_guide::publish_rise_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::unitree_guide::publish_rise_<ContainerAllocator> const> ConstPtr;

}; // struct publish_rise_

typedef ::unitree_guide::publish_rise_<std::allocator<void> > publish_rise;

typedef boost::shared_ptr< ::unitree_guide::publish_rise > publish_risePtr;
typedef boost::shared_ptr< ::unitree_guide::publish_rise const> publish_riseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::unitree_guide::publish_rise_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::unitree_guide::publish_rise_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::unitree_guide::publish_rise_<ContainerAllocator1> & lhs, const ::unitree_guide::publish_rise_<ContainerAllocator2> & rhs)
{
  return lhs.posError == rhs.posError &&
    lhs.velError == rhs.velError &&
    lhs.Error2 == rhs.Error2 &&
    lhs.Error2_0 == rhs.Error2_0 &&
    lhs.intergral == rhs.intergral &&
    lhs.miu_t == rhs.miu_t &&
    lhs.templesgn == rhs.templesgn &&
    lhs.templemiu == rhs.templemiu &&
    lhs.data1 == rhs.data1 &&
    lhs.data2 == rhs.data2 &&
    lhs.data3 == rhs.data3 &&
    lhs.data4 == rhs.data4;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::unitree_guide::publish_rise_<ContainerAllocator1> & lhs, const ::unitree_guide::publish_rise_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace unitree_guide

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::unitree_guide::publish_rise_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::unitree_guide::publish_rise_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::unitree_guide::publish_rise_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::unitree_guide::publish_rise_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::unitree_guide::publish_rise_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::unitree_guide::publish_rise_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::unitree_guide::publish_rise_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4ce01dedb1e1719eddcff27609246b07";
  }

  static const char* value(const ::unitree_guide::publish_rise_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4ce01dedb1e1719eULL;
  static const uint64_t static_value2 = 0xddcff27609246b07ULL;
};

template<class ContainerAllocator>
struct DataType< ::unitree_guide::publish_rise_<ContainerAllocator> >
{
  static const char* value()
  {
    return "unitree_guide/publish_rise";
  }

  static const char* value(const ::unitree_guide::publish_rise_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::unitree_guide::publish_rise_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[3] posError\n"
"float64[3] velError\n"
"float64[3] Error2\n"
"float64[3] Error2_0\n"
"float64[3] intergral\n"
"float64[3] miu_t\n"
"float64[3] templesgn\n"
"float64[3] templemiu\n"
"float64    data1\n"
"float64    data2\n"
"float64    data3\n"
"float64    data4\n"
;
  }

  static const char* value(const ::unitree_guide::publish_rise_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::unitree_guide::publish_rise_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.posError);
      stream.next(m.velError);
      stream.next(m.Error2);
      stream.next(m.Error2_0);
      stream.next(m.intergral);
      stream.next(m.miu_t);
      stream.next(m.templesgn);
      stream.next(m.templemiu);
      stream.next(m.data1);
      stream.next(m.data2);
      stream.next(m.data3);
      stream.next(m.data4);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct publish_rise_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::unitree_guide::publish_rise_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::unitree_guide::publish_rise_<ContainerAllocator>& v)
  {
    s << indent << "posError[]" << std::endl;
    for (size_t i = 0; i < v.posError.size(); ++i)
    {
      s << indent << "  posError[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.posError[i]);
    }
    s << indent << "velError[]" << std::endl;
    for (size_t i = 0; i < v.velError.size(); ++i)
    {
      s << indent << "  velError[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.velError[i]);
    }
    s << indent << "Error2[]" << std::endl;
    for (size_t i = 0; i < v.Error2.size(); ++i)
    {
      s << indent << "  Error2[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.Error2[i]);
    }
    s << indent << "Error2_0[]" << std::endl;
    for (size_t i = 0; i < v.Error2_0.size(); ++i)
    {
      s << indent << "  Error2_0[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.Error2_0[i]);
    }
    s << indent << "intergral[]" << std::endl;
    for (size_t i = 0; i < v.intergral.size(); ++i)
    {
      s << indent << "  intergral[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.intergral[i]);
    }
    s << indent << "miu_t[]" << std::endl;
    for (size_t i = 0; i < v.miu_t.size(); ++i)
    {
      s << indent << "  miu_t[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.miu_t[i]);
    }
    s << indent << "templesgn[]" << std::endl;
    for (size_t i = 0; i < v.templesgn.size(); ++i)
    {
      s << indent << "  templesgn[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.templesgn[i]);
    }
    s << indent << "templemiu[]" << std::endl;
    for (size_t i = 0; i < v.templemiu.size(); ++i)
    {
      s << indent << "  templemiu[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.templemiu[i]);
    }
    s << indent << "data1: ";
    Printer<double>::stream(s, indent + "  ", v.data1);
    s << indent << "data2: ";
    Printer<double>::stream(s, indent + "  ", v.data2);
    s << indent << "data3: ";
    Printer<double>::stream(s, indent + "  ", v.data3);
    s << indent << "data4: ";
    Printer<double>::stream(s, indent + "  ", v.data4);
  }
};

} // namespace message_operations
} // namespace ros

#endif // UNITREE_GUIDE_MESSAGE_PUBLISH_RISE_H
