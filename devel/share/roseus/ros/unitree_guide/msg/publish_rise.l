;; Auto-generated. Do not edit!


(when (boundp 'unitree_guide::publish_rise)
  (if (not (find-package "UNITREE_GUIDE"))
    (make-package "UNITREE_GUIDE"))
  (shadow 'publish_rise (find-package "UNITREE_GUIDE")))
(unless (find-package "UNITREE_GUIDE::PUBLISH_RISE")
  (make-package "UNITREE_GUIDE::PUBLISH_RISE"))

(in-package "ROS")
;;//! \htmlinclude publish_rise.msg.html


(defclass unitree_guide::publish_rise
  :super ros::object
  :slots (_posError _velError _Error2 _Error2_0 _intergral _miu_t _templesgn _templemiu _data1 _data2 _data3 _data4 ))

(defmethod unitree_guide::publish_rise
  (:init
   (&key
    ((:posError __posError) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:velError __velError) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:Error2 __Error2) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:Error2_0 __Error2_0) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:intergral __intergral) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:miu_t __miu_t) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:templesgn __templesgn) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:templemiu __templemiu) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:data1 __data1) 0.0)
    ((:data2 __data2) 0.0)
    ((:data3 __data3) 0.0)
    ((:data4 __data4) 0.0)
    )
   (send-super :init)
   (setq _posError __posError)
   (setq _velError __velError)
   (setq _Error2 __Error2)
   (setq _Error2_0 __Error2_0)
   (setq _intergral __intergral)
   (setq _miu_t __miu_t)
   (setq _templesgn __templesgn)
   (setq _templemiu __templemiu)
   (setq _data1 (float __data1))
   (setq _data2 (float __data2))
   (setq _data3 (float __data3))
   (setq _data4 (float __data4))
   self)
  (:posError
   (&optional __posError)
   (if __posError (setq _posError __posError)) _posError)
  (:velError
   (&optional __velError)
   (if __velError (setq _velError __velError)) _velError)
  (:Error2
   (&optional __Error2)
   (if __Error2 (setq _Error2 __Error2)) _Error2)
  (:Error2_0
   (&optional __Error2_0)
   (if __Error2_0 (setq _Error2_0 __Error2_0)) _Error2_0)
  (:intergral
   (&optional __intergral)
   (if __intergral (setq _intergral __intergral)) _intergral)
  (:miu_t
   (&optional __miu_t)
   (if __miu_t (setq _miu_t __miu_t)) _miu_t)
  (:templesgn
   (&optional __templesgn)
   (if __templesgn (setq _templesgn __templesgn)) _templesgn)
  (:templemiu
   (&optional __templemiu)
   (if __templemiu (setq _templemiu __templemiu)) _templemiu)
  (:data1
   (&optional __data1)
   (if __data1 (setq _data1 __data1)) _data1)
  (:data2
   (&optional __data2)
   (if __data2 (setq _data2 __data2)) _data2)
  (:data3
   (&optional __data3)
   (if __data3 (setq _data3 __data3)) _data3)
  (:data4
   (&optional __data4)
   (if __data4 (setq _data4 __data4)) _data4)
  (:serialization-length
   ()
   (+
    ;; float64[3] _posError
    (* 8    3)
    ;; float64[3] _velError
    (* 8    3)
    ;; float64[3] _Error2
    (* 8    3)
    ;; float64[3] _Error2_0
    (* 8    3)
    ;; float64[3] _intergral
    (* 8    3)
    ;; float64[3] _miu_t
    (* 8    3)
    ;; float64[3] _templesgn
    (* 8    3)
    ;; float64[3] _templemiu
    (* 8    3)
    ;; float64 _data1
    8
    ;; float64 _data2
    8
    ;; float64 _data3
    8
    ;; float64 _data4
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[3] _posError
     (dotimes (i 3)
       (sys::poke (elt _posError i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _velError
     (dotimes (i 3)
       (sys::poke (elt _velError i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _Error2
     (dotimes (i 3)
       (sys::poke (elt _Error2 i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _Error2_0
     (dotimes (i 3)
       (sys::poke (elt _Error2_0 i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _intergral
     (dotimes (i 3)
       (sys::poke (elt _intergral i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _miu_t
     (dotimes (i 3)
       (sys::poke (elt _miu_t i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _templesgn
     (dotimes (i 3)
       (sys::poke (elt _templesgn i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _templemiu
     (dotimes (i 3)
       (sys::poke (elt _templemiu i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _data1
       (sys::poke _data1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _data2
       (sys::poke _data2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _data3
       (sys::poke _data3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _data4
       (sys::poke _data4 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[3] _posError
   (dotimes (i (length _posError))
     (setf (elt _posError i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _velError
   (dotimes (i (length _velError))
     (setf (elt _velError i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _Error2
   (dotimes (i (length _Error2))
     (setf (elt _Error2 i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _Error2_0
   (dotimes (i (length _Error2_0))
     (setf (elt _Error2_0 i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _intergral
   (dotimes (i (length _intergral))
     (setf (elt _intergral i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _miu_t
   (dotimes (i (length _miu_t))
     (setf (elt _miu_t i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _templesgn
   (dotimes (i (length _templesgn))
     (setf (elt _templesgn i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _templemiu
   (dotimes (i (length _templemiu))
     (setf (elt _templemiu i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64 _data1
     (setq _data1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _data2
     (setq _data2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _data3
     (setq _data3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _data4
     (setq _data4 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get unitree_guide::publish_rise :md5sum-) "4ce01dedb1e1719eddcff27609246b07")
(setf (get unitree_guide::publish_rise :datatype-) "unitree_guide/publish_rise")
(setf (get unitree_guide::publish_rise :definition-)
      "float64[3] posError
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

")



(provide :unitree_guide/publish_rise "4ce01dedb1e1719eddcff27609246b07")


