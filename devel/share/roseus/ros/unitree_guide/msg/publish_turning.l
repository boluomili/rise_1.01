;; Auto-generated. Do not edit!


(when (boundp 'unitree_guide::publish_turning)
  (if (not (find-package "UNITREE_GUIDE"))
    (make-package "UNITREE_GUIDE"))
  (shadow 'publish_turning (find-package "UNITREE_GUIDE")))
(unless (find-package "UNITREE_GUIDE::PUBLISH_TURNING")
  (make-package "UNITREE_GUIDE::PUBLISH_TURNING"))

(in-package "ROS")
;;//! \htmlinclude publish_turning.msg.html


(defclass unitree_guide::publish_turning
  :super ros::object
  :slots (_q _q_d _w _w_d _err_q _err_w _disturbance _dkexi _U ))

(defmethod unitree_guide::publish_turning
  (:init
   (&key
    ((:q __q) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:q_d __q_d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:w __w) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:w_d __w_d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:err_q __err_q) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:err_w __err_w) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:disturbance __disturbance) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:dkexi __dkexi) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:U __U) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _q __q)
   (setq _q_d __q_d)
   (setq _w __w)
   (setq _w_d __w_d)
   (setq _err_q __err_q)
   (setq _err_w __err_w)
   (setq _disturbance __disturbance)
   (setq _dkexi __dkexi)
   (setq _U __U)
   self)
  (:q
   (&optional __q)
   (if __q (setq _q __q)) _q)
  (:q_d
   (&optional __q_d)
   (if __q_d (setq _q_d __q_d)) _q_d)
  (:w
   (&optional __w)
   (if __w (setq _w __w)) _w)
  (:w_d
   (&optional __w_d)
   (if __w_d (setq _w_d __w_d)) _w_d)
  (:err_q
   (&optional __err_q)
   (if __err_q (setq _err_q __err_q)) _err_q)
  (:err_w
   (&optional __err_w)
   (if __err_w (setq _err_w __err_w)) _err_w)
  (:disturbance
   (&optional __disturbance)
   (if __disturbance (setq _disturbance __disturbance)) _disturbance)
  (:dkexi
   (&optional __dkexi)
   (if __dkexi (setq _dkexi __dkexi)) _dkexi)
  (:U
   (&optional __U)
   (if __U (setq _U __U)) _U)
  (:serialization-length
   ()
   (+
    ;; float64[3] _q
    (* 8    3)
    ;; float64[3] _q_d
    (* 8    3)
    ;; float64[3] _w
    (* 8    3)
    ;; float64[3] _w_d
    (* 8    3)
    ;; float64[3] _err_q
    (* 8    3)
    ;; float64[3] _err_w
    (* 8    3)
    ;; float64[3] _disturbance
    (* 8    3)
    ;; float64[3] _dkexi
    (* 8    3)
    ;; float64[3] _U
    (* 8    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[3] _q
     (dotimes (i 3)
       (sys::poke (elt _q i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _q_d
     (dotimes (i 3)
       (sys::poke (elt _q_d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _w
     (dotimes (i 3)
       (sys::poke (elt _w i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _w_d
     (dotimes (i 3)
       (sys::poke (elt _w_d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _err_q
     (dotimes (i 3)
       (sys::poke (elt _err_q i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _err_w
     (dotimes (i 3)
       (sys::poke (elt _err_w i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _disturbance
     (dotimes (i 3)
       (sys::poke (elt _disturbance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _dkexi
     (dotimes (i 3)
       (sys::poke (elt _dkexi i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _U
     (dotimes (i 3)
       (sys::poke (elt _U i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[3] _q
   (dotimes (i (length _q))
     (setf (elt _q i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _q_d
   (dotimes (i (length _q_d))
     (setf (elt _q_d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _w
   (dotimes (i (length _w))
     (setf (elt _w i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _w_d
   (dotimes (i (length _w_d))
     (setf (elt _w_d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _err_q
   (dotimes (i (length _err_q))
     (setf (elt _err_q i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _err_w
   (dotimes (i (length _err_w))
     (setf (elt _err_w i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _disturbance
   (dotimes (i (length _disturbance))
     (setf (elt _disturbance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _dkexi
   (dotimes (i (length _dkexi))
     (setf (elt _dkexi i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _U
   (dotimes (i (length _U))
     (setf (elt _U i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get unitree_guide::publish_turning :md5sum-) "e4c34f17a8050a37a9187972a1aa7595")
(setf (get unitree_guide::publish_turning :datatype-) "unitree_guide/publish_turning")
(setf (get unitree_guide::publish_turning :definition-)
      "float64[3] q
float64[3] q_d
float64[3] w
float64[3] w_d
float64[3] err_q
float64[3] err_w
float64[3] disturbance
float64[3] dkexi
float64[3] U
")



(provide :unitree_guide/publish_turning "e4c34f17a8050a37a9187972a1aa7595")


