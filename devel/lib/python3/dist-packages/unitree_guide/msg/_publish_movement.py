# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from unitree_guide/publish_movement.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class publish_movement(genpy.Message):
  _md5sum = "4c2667fbdf93769a18b4f3cfd1a37df8"
  _type = "unitree_guide/publish_movement"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float64[3] p
float64[3] p_d
float64[3] err_p
float64[3] v
float64[3] v_d
float64[3] err_v
float64[3] a
float64[3] a_d
float64 sumfootforce 
float64 d_mp
float64 pos_error_0"""
  __slots__ = ['p','p_d','err_p','v','v_d','err_v','a','a_d','sumfootforce','d_mp','pos_error_0']
  _slot_types = ['float64[3]','float64[3]','float64[3]','float64[3]','float64[3]','float64[3]','float64[3]','float64[3]','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       p,p_d,err_p,v,v_d,err_v,a,a_d,sumfootforce,d_mp,pos_error_0

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(publish_movement, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.p is None:
        self.p = [0.] * 3
      if self.p_d is None:
        self.p_d = [0.] * 3
      if self.err_p is None:
        self.err_p = [0.] * 3
      if self.v is None:
        self.v = [0.] * 3
      if self.v_d is None:
        self.v_d = [0.] * 3
      if self.err_v is None:
        self.err_v = [0.] * 3
      if self.a is None:
        self.a = [0.] * 3
      if self.a_d is None:
        self.a_d = [0.] * 3
      if self.sumfootforce is None:
        self.sumfootforce = 0.
      if self.d_mp is None:
        self.d_mp = 0.
      if self.pos_error_0 is None:
        self.pos_error_0 = 0.
    else:
      self.p = [0.] * 3
      self.p_d = [0.] * 3
      self.err_p = [0.] * 3
      self.v = [0.] * 3
      self.v_d = [0.] * 3
      self.err_v = [0.] * 3
      self.a = [0.] * 3
      self.a_d = [0.] * 3
      self.sumfootforce = 0.
      self.d_mp = 0.
      self.pos_error_0 = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      buff.write(_get_struct_3d().pack(*self.p))
      buff.write(_get_struct_3d().pack(*self.p_d))
      buff.write(_get_struct_3d().pack(*self.err_p))
      buff.write(_get_struct_3d().pack(*self.v))
      buff.write(_get_struct_3d().pack(*self.v_d))
      buff.write(_get_struct_3d().pack(*self.err_v))
      buff.write(_get_struct_3d().pack(*self.a))
      buff.write(_get_struct_3d().pack(*self.a_d))
      _x = self
      buff.write(_get_struct_3d().pack(_x.sumfootforce, _x.d_mp, _x.pos_error_0))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 24
      self.p = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.p_d = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.err_p = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.v = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.v_d = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.err_v = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.a = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.a_d = _get_struct_3d().unpack(str[start:end])
      _x = self
      start = end
      end += 24
      (_x.sumfootforce, _x.d_mp, _x.pos_error_0,) = _get_struct_3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      buff.write(self.p.tostring())
      buff.write(self.p_d.tostring())
      buff.write(self.err_p.tostring())
      buff.write(self.v.tostring())
      buff.write(self.v_d.tostring())
      buff.write(self.err_v.tostring())
      buff.write(self.a.tostring())
      buff.write(self.a_d.tostring())
      _x = self
      buff.write(_get_struct_3d().pack(_x.sumfootforce, _x.d_mp, _x.pos_error_0))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 24
      self.p = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.p_d = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.err_p = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.v = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.v_d = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.err_v = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.a = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.a_d = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      _x = self
      start = end
      end += 24
      (_x.sumfootforce, _x.d_mp, _x.pos_error_0,) = _get_struct_3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3d = None
def _get_struct_3d():
    global _struct_3d
    if _struct_3d is None:
        _struct_3d = struct.Struct("<3d")
    return _struct_3d
