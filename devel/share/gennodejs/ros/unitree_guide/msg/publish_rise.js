// Auto-generated. Do not edit!

// (in-package unitree_guide.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class publish_rise {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.posError = null;
      this.velError = null;
      this.Error2 = null;
      this.Error2_0 = null;
      this.intergral = null;
      this.miu_t = null;
      this.templesgn = null;
      this.templemiu = null;
      this.data1 = null;
      this.data2 = null;
      this.data3 = null;
      this.data4 = null;
    }
    else {
      if (initObj.hasOwnProperty('posError')) {
        this.posError = initObj.posError
      }
      else {
        this.posError = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('velError')) {
        this.velError = initObj.velError
      }
      else {
        this.velError = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Error2')) {
        this.Error2 = initObj.Error2
      }
      else {
        this.Error2 = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Error2_0')) {
        this.Error2_0 = initObj.Error2_0
      }
      else {
        this.Error2_0 = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('intergral')) {
        this.intergral = initObj.intergral
      }
      else {
        this.intergral = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('miu_t')) {
        this.miu_t = initObj.miu_t
      }
      else {
        this.miu_t = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('templesgn')) {
        this.templesgn = initObj.templesgn
      }
      else {
        this.templesgn = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('templemiu')) {
        this.templemiu = initObj.templemiu
      }
      else {
        this.templemiu = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('data1')) {
        this.data1 = initObj.data1
      }
      else {
        this.data1 = 0.0;
      }
      if (initObj.hasOwnProperty('data2')) {
        this.data2 = initObj.data2
      }
      else {
        this.data2 = 0.0;
      }
      if (initObj.hasOwnProperty('data3')) {
        this.data3 = initObj.data3
      }
      else {
        this.data3 = 0.0;
      }
      if (initObj.hasOwnProperty('data4')) {
        this.data4 = initObj.data4
      }
      else {
        this.data4 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type publish_rise
    // Check that the constant length array field [posError] has the right length
    if (obj.posError.length !== 3) {
      throw new Error('Unable to serialize array field posError - length must be 3')
    }
    // Serialize message field [posError]
    bufferOffset = _arraySerializer.float64(obj.posError, buffer, bufferOffset, 3);
    // Check that the constant length array field [velError] has the right length
    if (obj.velError.length !== 3) {
      throw new Error('Unable to serialize array field velError - length must be 3')
    }
    // Serialize message field [velError]
    bufferOffset = _arraySerializer.float64(obj.velError, buffer, bufferOffset, 3);
    // Check that the constant length array field [Error2] has the right length
    if (obj.Error2.length !== 3) {
      throw new Error('Unable to serialize array field Error2 - length must be 3')
    }
    // Serialize message field [Error2]
    bufferOffset = _arraySerializer.float64(obj.Error2, buffer, bufferOffset, 3);
    // Check that the constant length array field [Error2_0] has the right length
    if (obj.Error2_0.length !== 3) {
      throw new Error('Unable to serialize array field Error2_0 - length must be 3')
    }
    // Serialize message field [Error2_0]
    bufferOffset = _arraySerializer.float64(obj.Error2_0, buffer, bufferOffset, 3);
    // Check that the constant length array field [intergral] has the right length
    if (obj.intergral.length !== 3) {
      throw new Error('Unable to serialize array field intergral - length must be 3')
    }
    // Serialize message field [intergral]
    bufferOffset = _arraySerializer.float64(obj.intergral, buffer, bufferOffset, 3);
    // Check that the constant length array field [miu_t] has the right length
    if (obj.miu_t.length !== 3) {
      throw new Error('Unable to serialize array field miu_t - length must be 3')
    }
    // Serialize message field [miu_t]
    bufferOffset = _arraySerializer.float64(obj.miu_t, buffer, bufferOffset, 3);
    // Check that the constant length array field [templesgn] has the right length
    if (obj.templesgn.length !== 3) {
      throw new Error('Unable to serialize array field templesgn - length must be 3')
    }
    // Serialize message field [templesgn]
    bufferOffset = _arraySerializer.float64(obj.templesgn, buffer, bufferOffset, 3);
    // Check that the constant length array field [templemiu] has the right length
    if (obj.templemiu.length !== 3) {
      throw new Error('Unable to serialize array field templemiu - length must be 3')
    }
    // Serialize message field [templemiu]
    bufferOffset = _arraySerializer.float64(obj.templemiu, buffer, bufferOffset, 3);
    // Serialize message field [data1]
    bufferOffset = _serializer.float64(obj.data1, buffer, bufferOffset);
    // Serialize message field [data2]
    bufferOffset = _serializer.float64(obj.data2, buffer, bufferOffset);
    // Serialize message field [data3]
    bufferOffset = _serializer.float64(obj.data3, buffer, bufferOffset);
    // Serialize message field [data4]
    bufferOffset = _serializer.float64(obj.data4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type publish_rise
    let len;
    let data = new publish_rise(null);
    // Deserialize message field [posError]
    data.posError = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [velError]
    data.velError = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [Error2]
    data.Error2 = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [Error2_0]
    data.Error2_0 = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [intergral]
    data.intergral = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [miu_t]
    data.miu_t = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [templesgn]
    data.templesgn = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [templemiu]
    data.templemiu = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [data1]
    data.data1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [data2]
    data.data2 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [data3]
    data.data3 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [data4]
    data.data4 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 224;
  }

  static datatype() {
    // Returns string type for a message object
    return 'unitree_guide/publish_rise';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4ce01dedb1e1719eddcff27609246b07';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[3] posError
    float64[3] velError
    float64[3] Error2
    float64[3] Error2_0
    float64[3] intergral
    float64[3] miu_t
    float64[3] templesgn
    float64[3] templemiu
    float64    data1
    float64    data2
    float64    data3
    float64    data4
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new publish_rise(null);
    if (msg.posError !== undefined) {
      resolved.posError = msg.posError;
    }
    else {
      resolved.posError = new Array(3).fill(0)
    }

    if (msg.velError !== undefined) {
      resolved.velError = msg.velError;
    }
    else {
      resolved.velError = new Array(3).fill(0)
    }

    if (msg.Error2 !== undefined) {
      resolved.Error2 = msg.Error2;
    }
    else {
      resolved.Error2 = new Array(3).fill(0)
    }

    if (msg.Error2_0 !== undefined) {
      resolved.Error2_0 = msg.Error2_0;
    }
    else {
      resolved.Error2_0 = new Array(3).fill(0)
    }

    if (msg.intergral !== undefined) {
      resolved.intergral = msg.intergral;
    }
    else {
      resolved.intergral = new Array(3).fill(0)
    }

    if (msg.miu_t !== undefined) {
      resolved.miu_t = msg.miu_t;
    }
    else {
      resolved.miu_t = new Array(3).fill(0)
    }

    if (msg.templesgn !== undefined) {
      resolved.templesgn = msg.templesgn;
    }
    else {
      resolved.templesgn = new Array(3).fill(0)
    }

    if (msg.templemiu !== undefined) {
      resolved.templemiu = msg.templemiu;
    }
    else {
      resolved.templemiu = new Array(3).fill(0)
    }

    if (msg.data1 !== undefined) {
      resolved.data1 = msg.data1;
    }
    else {
      resolved.data1 = 0.0
    }

    if (msg.data2 !== undefined) {
      resolved.data2 = msg.data2;
    }
    else {
      resolved.data2 = 0.0
    }

    if (msg.data3 !== undefined) {
      resolved.data3 = msg.data3;
    }
    else {
      resolved.data3 = 0.0
    }

    if (msg.data4 !== undefined) {
      resolved.data4 = msg.data4;
    }
    else {
      resolved.data4 = 0.0
    }

    return resolved;
    }
};

module.exports = publish_rise;
