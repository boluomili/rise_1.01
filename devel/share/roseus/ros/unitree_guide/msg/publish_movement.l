;; Auto-generated. Do not edit!


(when (boundp 'unitree_guide::publish_movement)
  (if (not (find-package "UNITREE_GUIDE"))
    (make-package "UNITREE_GUIDE"))
  (shadow 'publish_movement (find-package "UNITREE_GUIDE")))
(unless (find-package "UNITREE_GUIDE::PUBLISH_MOVEMENT")
  (make-package "UNITREE_GUIDE::PUBLISH_MOVEMENT"))

(in-package "ROS")
;;//! \htmlinclude publish_movement.msg.html


(defclass unitree_guide::publish_movement
  :super ros::object
  :slots (_p _p_d _err_p _v _v_d _err_v _a _a_d _sumfootforce _d_mp _pos_error_0 ))

(defmethod unitree_guide::publish_movement
  (:init
   (&key
    ((:p __p) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:p_d __p_d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:err_p __err_p) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:v __v) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:v_d __v_d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:err_v __err_v) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:a __a) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:a_d __a_d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:sumfootforce __sumfootforce) 0.0)
    ((:d_mp __d_mp) 0.0)
    ((:pos_error_0 __pos_error_0) 0.0)
    )
   (send-super :init)
   (setq _p __p)
   (setq _p_d __p_d)
   (setq _err_p __err_p)
   (setq _v __v)
   (setq _v_d __v_d)
   (setq _err_v __err_v)
   (setq _a __a)
   (setq _a_d __a_d)
   (setq _sumfootforce (float __sumfootforce))
   (setq _d_mp (float __d_mp))
   (setq _pos_error_0 (float __pos_error_0))
   self)
  (:p
   (&optional __p)
   (if __p (setq _p __p)) _p)
  (:p_d
   (&optional __p_d)
   (if __p_d (setq _p_d __p_d)) _p_d)
  (:err_p
   (&optional __err_p)
   (if __err_p (setq _err_p __err_p)) _err_p)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:v_d
   (&optional __v_d)
   (if __v_d (setq _v_d __v_d)) _v_d)
  (:err_v
   (&optional __err_v)
   (if __err_v (setq _err_v __err_v)) _err_v)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:a_d
   (&optional __a_d)
   (if __a_d (setq _a_d __a_d)) _a_d)
  (:sumfootforce
   (&optional __sumfootforce)
   (if __sumfootforce (setq _sumfootforce __sumfootforce)) _sumfootforce)
  (:d_mp
   (&optional __d_mp)
   (if __d_mp (setq _d_mp __d_mp)) _d_mp)
  (:pos_error_0
   (&optional __pos_error_0)
   (if __pos_error_0 (setq _pos_error_0 __pos_error_0)) _pos_error_0)
  (:serialization-length
   ()
   (+
    ;; float64[3] _p
    (* 8    3)
    ;; float64[3] _p_d
    (* 8    3)
    ;; float64[3] _err_p
    (* 8    3)
    ;; float64[3] _v
    (* 8    3)
    ;; float64[3] _v_d
    (* 8    3)
    ;; float64[3] _err_v
    (* 8    3)
    ;; float64[3] _a
    (* 8    3)
    ;; float64[3] _a_d
    (* 8    3)
    ;; float64 _sumfootforce
    8
    ;; float64 _d_mp
    8
    ;; float64 _pos_error_0
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[3] _p
     (dotimes (i 3)
       (sys::poke (elt _p i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _p_d
     (dotimes (i 3)
       (sys::poke (elt _p_d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _err_p
     (dotimes (i 3)
       (sys::poke (elt _err_p i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _v
     (dotimes (i 3)
       (sys::poke (elt _v i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _v_d
     (dotimes (i 3)
       (sys::poke (elt _v_d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _err_v
     (dotimes (i 3)
       (sys::poke (elt _err_v i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _a
     (dotimes (i 3)
       (sys::poke (elt _a i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _a_d
     (dotimes (i 3)
       (sys::poke (elt _a_d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _sumfootforce
       (sys::poke _sumfootforce (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _d_mp
       (sys::poke _d_mp (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _pos_error_0
       (sys::poke _pos_error_0 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[3] _p
   (dotimes (i (length _p))
     (setf (elt _p i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _p_d
   (dotimes (i (length _p_d))
     (setf (elt _p_d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _err_p
   (dotimes (i (length _err_p))
     (setf (elt _err_p i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _v
   (dotimes (i (length _v))
     (setf (elt _v i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _v_d
   (dotimes (i (length _v_d))
     (setf (elt _v_d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _err_v
   (dotimes (i (length _err_v))
     (setf (elt _err_v i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _a
   (dotimes (i (length _a))
     (setf (elt _a i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _a_d
   (dotimes (i (length _a_d))
     (setf (elt _a_d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64 _sumfootforce
     (setq _sumfootforce (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _d_mp
     (setq _d_mp (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _pos_error_0
     (setq _pos_error_0 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get unitree_guide::publish_movement :md5sum-) "4c2667fbdf93769a18b4f3cfd1a37df8")
(setf (get unitree_guide::publish_movement :datatype-) "unitree_guide/publish_movement")
(setf (get unitree_guide::publish_movement :definition-)
      "float64[3] p
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
")



(provide :unitree_guide/publish_movement "4c2667fbdf93769a18b4f3cfd1a37df8")


