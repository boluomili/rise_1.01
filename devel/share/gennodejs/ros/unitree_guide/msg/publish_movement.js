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

class publish_movement {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.p = null;
      this.p_d = null;
      this.err_p = null;
      this.v = null;
      this.v_d = null;
      this.err_v = null;
      this.a = null;
      this.a_d = null;
      this.sumfootforce = null;
      this.d_mp = null;
      this.pos_error_0 = null;
    }
    else {
      if (initObj.hasOwnProperty('p')) {
        this.p = initObj.p
      }
      else {
        this.p = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('p_d')) {
        this.p_d = initObj.p_d
      }
      else {
        this.p_d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('err_p')) {
        this.err_p = initObj.err_p
      }
      else {
        this.err_p = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('v')) {
        this.v = initObj.v
      }
      else {
        this.v = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('v_d')) {
        this.v_d = initObj.v_d
      }
      else {
        this.v_d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('err_v')) {
        this.err_v = initObj.err_v
      }
      else {
        this.err_v = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('a')) {
        this.a = initObj.a
      }
      else {
        this.a = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('a_d')) {
        this.a_d = initObj.a_d
      }
      else {
        this.a_d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('sumfootforce')) {
        this.sumfootforce = initObj.sumfootforce
      }
      else {
        this.sumfootforce = 0.0;
      }
      if (initObj.hasOwnProperty('d_mp')) {
        this.d_mp = initObj.d_mp
      }
      else {
        this.d_mp = 0.0;
      }
      if (initObj.hasOwnProperty('pos_error_0')) {
        this.pos_error_0 = initObj.pos_error_0
      }
      else {
        this.pos_error_0 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type publish_movement
    // Check that the constant length array field [p] has the right length
    if (obj.p.length !== 3) {
      throw new Error('Unable to serialize array field p - length must be 3')
    }
    // Serialize message field [p]
    bufferOffset = _arraySerializer.float64(obj.p, buffer, bufferOffset, 3);
    // Check that the constant length array field [p_d] has the right length
    if (obj.p_d.length !== 3) {
      throw new Error('Unable to serialize array field p_d - length must be 3')
    }
    // Serialize message field [p_d]
    bufferOffset = _arraySerializer.float64(obj.p_d, buffer, bufferOffset, 3);
    // Check that the constant length array field [err_p] has the right length
    if (obj.err_p.length !== 3) {
      throw new Error('Unable to serialize array field err_p - length must be 3')
    }
    // Serialize message field [err_p]
    bufferOffset = _arraySerializer.float64(obj.err_p, buffer, bufferOffset, 3);
    // Check that the constant length array field [v] has the right length
    if (obj.v.length !== 3) {
      throw new Error('Unable to serialize array field v - length must be 3')
    }
    // Serialize message field [v]
    bufferOffset = _arraySerializer.float64(obj.v, buffer, bufferOffset, 3);
    // Check that the constant length array field [v_d] has the right length
    if (obj.v_d.length !== 3) {
      throw new Error('Unable to serialize array field v_d - length must be 3')
    }
    // Serialize message field [v_d]
    bufferOffset = _arraySerializer.float64(obj.v_d, buffer, bufferOffset, 3);
    // Check that the constant length array field [err_v] has the right length
    if (obj.err_v.length !== 3) {
      throw new Error('Unable to serialize array field err_v - length must be 3')
    }
    // Serialize message field [err_v]
    bufferOffset = _arraySerializer.float64(obj.err_v, buffer, bufferOffset, 3);
    // Check that the constant length array field [a] has the right length
    if (obj.a.length !== 3) {
      throw new Error('Unable to serialize array field a - length must be 3')
    }
    // Serialize message field [a]
    bufferOffset = _arraySerializer.float64(obj.a, buffer, bufferOffset, 3);
    // Check that the constant length array field [a_d] has the right length
    if (obj.a_d.length !== 3) {
      throw new Error('Unable to serialize array field a_d - length must be 3')
    }
    // Serialize message field [a_d]
    bufferOffset = _arraySerializer.float64(obj.a_d, buffer, bufferOffset, 3);
    // Serialize message field [sumfootforce]
    bufferOffset = _serializer.float64(obj.sumfootforce, buffer, bufferOffset);
    // Serialize message field [d_mp]
    bufferOffset = _serializer.float64(obj.d_mp, buffer, bufferOffset);
    // Serialize message field [pos_error_0]
    bufferOffset = _serializer.float64(obj.pos_error_0, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type publish_movement
    let len;
    let data = new publish_movement(null);
    // Deserialize message field [p]
    data.p = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [p_d]
    data.p_d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [err_p]
    data.err_p = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [v]
    data.v = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [v_d]
    data.v_d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [err_v]
    data.err_v = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [a]
    data.a = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [a_d]
    data.a_d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [sumfootforce]
    data.sumfootforce = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [d_mp]
    data.d_mp = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pos_error_0]
    data.pos_error_0 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 216;
  }

  static datatype() {
    // Returns string type for a message object
    return 'unitree_guide/publish_movement';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4c2667fbdf93769a18b4f3cfd1a37df8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[3] p
    float64[3] p_d
    float64[3] err_p
    float64[3] v
    float64[3] v_d
    float64[3] err_v
    float64[3] a
    float64[3] a_d
    float64 sumfootforce 
    float64 d_mp
    float64 pos_error_0
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new publish_movement(null);
    if (msg.p !== undefined) {
      resolved.p = msg.p;
    }
    else {
      resolved.p = new Array(3).fill(0)
    }

    if (msg.p_d !== undefined) {
      resolved.p_d = msg.p_d;
    }
    else {
      resolved.p_d = new Array(3).fill(0)
    }

    if (msg.err_p !== undefined) {
      resolved.err_p = msg.err_p;
    }
    else {
      resolved.err_p = new Array(3).fill(0)
    }

    if (msg.v !== undefined) {
      resolved.v = msg.v;
    }
    else {
      resolved.v = new Array(3).fill(0)
    }

    if (msg.v_d !== undefined) {
      resolved.v_d = msg.v_d;
    }
    else {
      resolved.v_d = new Array(3).fill(0)
    }

    if (msg.err_v !== undefined) {
      resolved.err_v = msg.err_v;
    }
    else {
      resolved.err_v = new Array(3).fill(0)
    }

    if (msg.a !== undefined) {
      resolved.a = msg.a;
    }
    else {
      resolved.a = new Array(3).fill(0)
    }

    if (msg.a_d !== undefined) {
      resolved.a_d = msg.a_d;
    }
    else {
      resolved.a_d = new Array(3).fill(0)
    }

    if (msg.sumfootforce !== undefined) {
      resolved.sumfootforce = msg.sumfootforce;
    }
    else {
      resolved.sumfootforce = 0.0
    }

    if (msg.d_mp !== undefined) {
      resolved.d_mp = msg.d_mp;
    }
    else {
      resolved.d_mp = 0.0
    }

    if (msg.pos_error_0 !== undefined) {
      resolved.pos_error_0 = msg.pos_error_0;
    }
    else {
      resolved.pos_error_0 = 0.0
    }

    return resolved;
    }
};

module.exports = publish_movement;
