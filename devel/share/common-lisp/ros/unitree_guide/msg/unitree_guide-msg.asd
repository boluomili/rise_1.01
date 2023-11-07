
(cl:in-package :asdf)

(defsystem "unitree_guide-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "publish_movement" :depends-on ("_package_publish_movement"))
    (:file "_package_publish_movement" :depends-on ("_package"))
    (:file "publish_rise" :depends-on ("_package_publish_rise"))
    (:file "_package_publish_rise" :depends-on ("_package"))
    (:file "publish_turning" :depends-on ("_package_publish_turning"))
    (:file "_package_publish_turning" :depends-on ("_package"))
  ))