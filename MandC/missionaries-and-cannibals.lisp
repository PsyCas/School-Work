;;Parakram Basnet
;; Assignment 5 Missionaries-And-Cannibals

;; Defines the state of the two shores at any given time
(defclass game-state (state)
    ((missionaries-right :initarg :missionaries :initform 0 :accessor missionaries-right :documentation "Number of missionaries on the right shore.")
     (missionaries-left :initarg :missionaries :initform 0 :accessor missionaries-left :documentation "Number of missionaries on the left shore.")
     (cannibals-right :initarg :cannibals :initform 0 :accessor cannibals-right :documentation "Number of cannibals on the right shore.")
     (cannibals-left :initarg :cannibals :initform 0 :accessor cannibals-left :documentation "Number of cannibals on the left shore.")
     (boat-position :initarg :cannibals :initform 0 :accessor boat-position :documentation "Number of cannibals on the boat." )))

(defparameter *missionaries-and-cannibals* 
  (make-instance 'problem 
    :start-state (make-instance 'game-state :missionaries-right 3 :missionaries-left 0 :cannibals-right: 3 :cannibals-left 0 :missionaries-boat 0 :cannibals-boat 0 :boat-position 'R)
    :goal-test 'all-on-leftp
    :operators '(take-two-missionaries, take-two-cannibals, take-missionary-cannibal, take-one-missionary, take-one-cannibal)
    :name "missionaries and cannibals"))

;; defining the goal state
(defmethod all-on-leftp ((self game-state))
    (and (equal (missionaries-left self) 3)
         (equal (cannibals-left self) 3)
         (eql (boat-position self) 'L)))

;;;****************************************************************************************
;;;SEARCH SUPPORT FUNCTIONS
;;;****************************************************************************************

(defmethod equal-states ((self new-jug-state) (other new-jug-state))
    (and (equal (missionaries-left self) (missionaries-left other))
         (equal (missionaries-right self) (missionaries-right other))
         (equal (cannibals-right self) (cannibals-right other))
         (equal (cannibals-left self) (cannibals-left other))
         (equal (boat-num self) (boat-num other))))

(defmethod copy-state ((self new-jug-state))
    (make-instance 'game-state  :missionaries-left (missionaries-left self) 
                                :missionaries-right (missionaries-right self)
                                :cannibals-right (cannibals-right self)
                                :cannibals-left (cannibals-left self)
                                :boat-num (boat-num self)))

(defmethod estimated-distance-from-goal ((self farmer-state))
    (loop for item in '(missionaries-right missionaries-left cannibals-left cannibals-right boat-num)
        count (equal (funcall item self) 'L)))

;;;****************************************************************************************
;;;OPERATORS AND THEIR SUPPORTING DEFINITIONS
;;;****************************************************************************************

;; checking conditions for safe moves
(defun safe (state)
    (cond   ((< (missionaries-left state) (cannibals-left state))
            nil)
            ((< (missionaries-right state) (cannibals-right state))
            nil)
            (t state)))

;; function that changes the boats position
(defun move-boat (side)
   (cond ((eql side 'L) 'R)
        ((eql side 'R) 'L))) 

;; Action that transfers 2 missionaries on the boat
(defun take-two-missionaries (state)
    (cond   ((and (eql (boat-position state) 'R) (> (missionaries-right state) 1)) 
            (let ((propsed (copy-state state)))
                 (setf (missionaries-right propsed) (- (missionaries-right state) 2))
                 (setf (missionaries-left propsed) (+ (missionaries-left state) 2))))
            (and (eql (boat-position state) 'L) (> (missionaries-left state) 1))
            (let ((propsed (copy-state state)))
                 (setf (missionaries-left propsed) (- (missionaries-right state) 2))
                 (setf (missionaries-right propsed) (+ (missionaries-right state) 2))))
    (setf (boat-position propsed) (move-boat (boat-position state)))
    (safe propsed))

;; action that takes two cannibals
(defun take-two-cannibals (state)
    (cond   ((and (eql (boat-position state) 'R) (> (cannibals-right state) 2)) 
            (let ((propsed (copy-state state)))
                 (setf (cannibals-right propsed) (- (cannibals-right state) 2))
                 (setf (cannibals-left propsed) (+ (cannibals-left state) 2))))
            (and (eql (boat-position state) 'L) (> (cannibals-left state) 2))
            (let ((propsed (copy-state state)))
                 (setf (cannibals-left propsed) (- (cannibals-right state) 2))
                 (setf (cannibals-right propsed) (+ (cannibals-right state) 2))))
    (setf (boat-position propsed) (move-boat (boat-position state)))
    (safe propsed))


;; action that takes one missionary and one cannibal
(defun take-missionary-cannibal (state)
   (cond   ((and (eql (boat-position state) 'R) (> (cannibals-right state) 2)) 
            (let ((propsed (copy-state state)))
                 (setf (cannibals-right propsed) (- (cannibals-right state) 2))
                 (setf (cannibals-left propsed) (+ (cannibals-left state) 2))))
            (and (eql (boat-position state) 'L) (> (cannibals-left state) 2))
            (let ((propsed (copy-state state)))
                 (setf (cannibals-left propsed) (- (cannibals-right state) 2))
                 (setf (cannibals-right propsed) (+ (cannibals-right state) 2))))
    (setf (boat-position propsed) (move-boat (boat-position state)))
    (safe propsed)) 

