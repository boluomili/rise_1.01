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

class publish_turning {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.q = null;
      this.q_d = null;
      this.w = null;
      this.w_d = null;
      this.err_q = null;
      this.err_w = null;
      this.disturbance = null;
      this.dkexi = null;
      this.U = null;
    }
    else {
      if (initObj.hasOwnProperty('q')) {
        this.q = initObj.q
      }
      else {
        this.q = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('q_d')) {
        this.q_d = initObj.q_d
      }
      else {
        this.q_d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('w')) {
        this.w = initObj.w
      }
      else {
        this.w = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('w_d')) {
        this.w_d = initObj.w_d
      }
      else {
        this.w_d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('err_q')) {
        this.err_q = initObj.err_q
      }
      else {
        this.err_q = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('err_w')) {
        this.err_w = initObj.err_w
      }
      else {
        this.err_w = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('disturbance')) {
        this.disturbance = initObj.disturbance
      }
      else {
        this.disturbance = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('dkexi')) {
        this.dkexi = initObj.dkexi
      }
      else {
        this.dkexi = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('U')) {
        this.U = initObj.U
      }
      else {
        this.U = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type publish_turning
    // Check that the constant length array field [q] has the right length
    if (obj.q.length !== 3) {
      throw new Error('Unable to serialize array field q - length must be 3')
    }
    // Serialize message field [q]
    bufferOffset = _arraySerializer.float64(obj.q, buffer, bufferOffset, 3);
    // Check that the constant length array field [q_d] has the right length
    if (obj.q_d.length !== 3) {
      throw new Error('Unable to serialize array field q_d - length must be 3')
    }
    // Serialize message field [q_d]
    bufferOffset = _arraySerializer.float64(obj.q_d, buffer, bufferOffset, 3);
    // Check that the constant length array field [w] has the right length
    if (obj.w.length !== 3) {
      throw new Error('Unable to serialize array field w - length must be 3')
    }
    // Serialize message field [w]
    bufferOffset = _arraySerializer.float64(obj.w, buffer, bufferOffset, 3);
    // Check that the constant length array field [w_d] has the right length
    if (obj.w_d.length !== 3) {
      throw new Error('Unable to serialize array field w_d - length must be 3')
    }
    // Serialize message field [w_d]
    bufferOffset = _arraySerializer.float64(obj.w_d, buffer, bufferOffset, 3);
    // Check that the constant length array field [err_q] has the right length
    if (obj.err_q.length !== 3) {
      throw new Error('Unable to serialize array field err_q - length must be 3')
    }
    // Serialize message field [err_q]
    bufferOffset = _arraySerializer.float64(obj.err_q, buffer, bufferOffset, 3);
    // Check that the constant length array field [err_w] has the right length
    if (obj.err_w.length !== 3) {
      throw new Error('Unable to serialize array field err_w - length must be 3')
    }
    // Serialize message field [err_w]
    bufferOffset = _arraySerializer.float64(obj.err_w, buffer, bufferOffset, 3);
    // Check that the constant length array field [disturbance] has the right length
    if (obj.disturbance.length !== 3) {
      throw new Error('Unable to serialize array field disturbance - length must be 3')
    }
    // Serialize message field [disturbance]
    bufferOffset = _arraySerializer.float64(obj.disturbance, buffer, bufferOffset, 3);
    // Check that the constant length array field [dkexi] has the right length
    if (obj.dkexi.length !== 3) {
      throw new Error('Unable to serialize array field dkexi - length must be 3')
    }
    // Serialize message field [dkexi]
    bufferOffset = _arraySerializer.float64(obj.dkexi, buffer, bufferOffset, 3);
    // Check that the constant length array field [U] has the right length
    if (obj.U.length !== 3) {
      throw new Error('Unable to serialize array field U - length must be 3')
    }
    // Serialize message field [U]
    bufferOffset = _arraySerializer.float64(obj.U, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type publish_turning
    let len;
    let data = new publish_turning(null);
    // Deserialize message field [q]
    data.q = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [q_d]
    data.q_d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [w]
    data.w = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [w_d]
    data.w_d = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [err_q]
    data.err_q = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [err_w]
    data.err_w = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [disturbance]
    data.disturbance = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [dkexi]
    data.dkexi = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [U]
    data.U = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 216;
  }

  static datatype() {
    // Returns string type for a message object
    return 'unitree_guide/publish_turning';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e4c34f17a8050a37a9187972a1aa7595';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[3] q
    float64[3] q_d
    float64[3] w
    float64[3] w_d
    float64[3] err_q
    float64[3] err_w
    float64[3] disturbance
    float64[3] dkexi
    float64[3] U
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new publish_turning(null);
    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = new Array(3).fill(0)
    }

    if (msg.q_d !== undefined) {
      resolved.q_d = msg.q_d;
    }
    else {
      resolved.q_d = new Array(3).fill(0)
    }

    if (msg.w !== undefined) {
      resolved.w = msg.w;
    }
    else {
      resolved.w = new Array(3).fill(0)
    }

    if (msg.w_d !== undefined) {
      resolved.w_d = msg.w_d;
    }
    else {
      resolved.w_d = new Array(3).fill(0)
    }

    if (msg.err_q !== undefined) {
      resolved.err_q = msg.err_q;
    }
    else {
      resolved.err_q = new Array(3).fill(0)
    }

    if (msg.err_w !== undefined) {
      resolved.err_w = msg.err_w;
    }
    else {
      resolved.err_w = new Array(3).fill(0)
    }

    if (msg.disturbance !== undefined) {
      resolved.disturbance = msg.disturbance;
    }
    else {
      resolved.disturbance = new Array(3).fill(0)
    }

    if (msg.dkexi !== undefined) {
      resolved.dkexi = msg.dkexi;
    }
    else {
      resolved.dkexi = new Array(3).fill(0)
    }

    if (msg.U !== undefined) {
      resolved.U = msg.U;
    }
    else {
      resolved.U = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = publish_turning;
