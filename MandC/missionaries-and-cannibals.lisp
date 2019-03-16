;;;****************************************************************************************
;;;THIS PROVIDES THE FOUNDATION FOR CLOS AI SEARCH
;;;to be used concurrently with a problem file
;;;****************************************************************************************

;;;****************************************************************************************
;;;Search STATISTICS
;;;****************************************************************************************
(defclass search-statistics ()
  ((nodes-generated :initarg :nodes-generated :initform 0 :accessor nodes-generated)
   (nodes-expanded :initarg :nodes-expanded :initform 0 :accessor nodes-expanded)
   (maximum-frontier :initarg :maximum-frontier :initform 0 :accessor maximum-frontier)
   (length-of-solution :initarg :length-of-solution :initform 0 :accessor length-of-solution)
   (maximum-depth :initarg :maximum-depth :initform 0 :accessor maximum-depth)))
  
;;;****************************************************************************************
;;;CLASS DEFINITIONS
;;;****************************************************************************************

(defclass problem ()
  ((name :initarg :name :initform nil :accessor name)
   (start-state :initarg :start-state :initform nil :accessor start-state)
   (goal-test :initarg :goal-test :initform nil :accessor goal-test)
   (operators :initarg :operators :initform nil :accessor operators)
   (statistics :initarg :statistics :initform (make-instance 'search-statistics) :accessor statistics)))

(defmethod reset-statistics ((self problem))
  (setf (statistics self) (make-instance 'search-statistics)))
  
(defparameter *trace-search* nil)

;the following  should be redefined for each problem
(defclass state ()
  ())

(defmethod equal-states ((self state) (other state))
  ())

(defmethod copy-state ((self state))
  ())

(defmethod estimated-distance-from-goal ((self state))
  ())

(defmethod printer ((self state))
  ())

(defclass node ()
  ((state :initarg :state :initform nil :accessor state)
   (problem :initarg :problem :initform nil :accessor problem)
   (path :initarg :path :initform nil :accessor path)
   (ancestors :initarg :ancestors :initform nil :accessor ancestors)))
  
(defmethod update-statistics ((self problem) expand frontier)
  (let ((stats (statistics self)))
    (when (> (length frontier) (maximum-frontier stats))
      (setf (maximum-frontier stats) (length frontier)))
    (when (> (length (path expand)) (maximum-depth stats))
      (setf (maximum-depth stats) (length (path expand))))))

;;;****************************************************************************************
;;;GENERAL FUNCTIONS 
;;;****************************************************************************************

;adds atom to the end of list
(defun add-to-end (atom list)
  (append list (list atom)))

;finds the successor of state resulting from application of operator
(defun successor-state (state operator)
  (funcall operator state))

;makes successor node from successor of state
(defmethod successor-node ((self node) operator)
  (let ((next (successor-state (state self) operator)))
    (when next
      (make-instance 'node :state next :path (add-to-end operator (path self)) :problem (problem self)))))

(defmethod reached-the-goal ((self node))
  (funcall (goal-test (problem self)) (state self)))

;;;****************************************************************************************
;;;BREADTH FIRST SEARCH DEFINITIONS
;;;****************************************************************************************

(defmethod finish-successful-search ((self problem) expand)
  (setf (length-of-solution (statistics self)) (length (path expand)))
  (describe (statistics self))
  (format t "%")
  (describe expand)
  expand)

;;generated is a list of states generated
;;expanded is a list of states expanded
;;frontier is a list of nodes to be expanded
(defmethod breadth-first-search ((self problem)) 
  (reset-statistics self)
  (format t "~%Performing breadth first search on problem ~a.~%" (name self))
  (let* ((initial-state (start-state self))
	 (frontier (list (make-instance 'node :state initial-state :path nil :problem self)))
	 (operators (operators self))
	 (generated (list initial-state))
	 solved expanded expand)
    (loop until (or solved (null frontier))
       do (setf expand (pop frontier)) 
	 (incf (nodes-expanded (statistics self)))
	 (push (state expand) expanded) 
	 (when *trace-search* (format t "~%~%Exploring ~a" (describe expand)))
	 (loop for operator in operators
	    for child = (successor-node expand operator) ;this is a node
	    for state = (when child (state child)) ;this is a state 
	    do (cond ((null child) nil)
		     ((reached-the-goal child)
		      (setf solved t)
		      (update-statistics self child frontier)
		      (finish-successful-search self child))
		     ((and (not (already-statep state expanded)) (not (already-nodep state frontier)))
		      (incf (nodes-generated (statistics self)))
		      (push state generated)
		      (setf frontier (add-to-end child frontier))
		      (update-statistics self child frontier))
		     (t nil)))
	 finally (when solved (return t)))))
  
(defparameter *trace-search* nil)


;state is equal to some state in list (there has to be an equal-states method defined)
(defun already-statep (state list)
  (member state list :test 'equal-states))

;state is equal to state of some node in list (there has to be an equal-states method defined)
(defun already-nodep (state list)
  (loop for node in list
       thereis (equal-states state (state node))))

;;***********************************************************************************************************************************

;;Parakram Basnet
;; Assignment 5 Missionaries-And-Cannibals

;; Defines the state of the two shores at any given time
(defclass game-state (state)
    ((missionaries-right :initarg :missionaries-right :initform nil :accessor missionaries-right :documentation "Number of missionaries on the right shore.")
     (missionaries-left :initarg :missionaries-left :initform nil :accessor missionaries-left :documentation "Number of missionaries on the left shore.")
     (cannibals-right :initarg :cannibals-right :initform nil :accessor cannibals-right :documentation "Number of cannibals on the right shore.")
     (cannibals-left :initarg :cannibals-left :initform nil :accessor cannibals-left :documentation "Number of cannibals on the left shore.")
     (boat-position :initarg :boat-position :initform nil :accessor boat-position :documentation "Number of cannibals on the boat." )))

(defparameter *missionaries-and-cannibals* 
  (make-instance 'problem 
    :start-state (make-instance 'game-state :missionaries-right 3 :missionaries-left 0 :cannibals-right 3 :cannibals-left 0 :boat-position 'R)
    :goal-test 'all-on-leftp
    :operators '(take-two-missionaries take-two-cannibals take-missionary-cannibal take-one-missionary take-one-cannibal)
    :name "missionaries and cannibals"))

;; defining the goal state
(defmethod all-on-leftp ((self game-state))
    (and (equal (missionaries-left self) 3)
         (equal (cannibals-left self) 3)))

;;;****************************************************************************************
;;;SEARCH SUPPORT FUNCTIONS
;;;****************************************************************************************

(defmethod equal-states ((self game-state) (other game-state))
    (and (equal (missionaries-left self) (missionaries-left other))
         (equal (missionaries-right self) (missionaries-right other))
         (equal (cannibals-right self) (cannibals-right other))
         (equal (cannibals-left self) (cannibals-left other))
         (equal (boat-position self) (boat-position other))))

(defmethod copy-state ((self game-state))
    (make-instance 'game-state  :missionaries-left (missionaries-left self) 
                                :missionaries-right (missionaries-right self)
                                :cannibals-right (cannibals-right self)
                                :cannibals-left (cannibals-left self)
                                :boat-position (boat-position self)))

(defmethod estimated-distance-from-goal ((self game-state))
    (loop for item in '(missionaries-right missionaries-left cannibals-left cannibals-right boat-position)
        count (equal (funcall item self) 'L)))

;;;****************************************************************************************
;;;OPERATORS AND THEIR SUPPORTING DEFINITIONS
;;;****************************************************************************************

;; checking conditions for safe moves
(defun safe(state)
    (cond   ((and   (< (missionaries-left state) (cannibals-left state)) 
                    (not (eql (missionaries-left state) 0)))
            nil)
            ((and   (< (missionaries-right state) (cannibals-right state)) 
                    (not (eql (missionaries-right state) 0)))
            nil)
            (t state))) 

;; function that changes the boats position
(defun move-boat (side)
    (write side)
    (cond ((eql side 'L) 'R)
          ((eql side 'R) 'L))) 

;; Action that transfers 2 missionaries on the boat
(defun take-two-missionaries (state)
    (write "take-two-missionaries")
    (cond   ((and (eql (boat-position state) 'R) (> (missionaries-right state) 1)) 
             (let ((proposed (copy-state state))) 
                (write "I am RIGHT")
                 (setf (missionaries-right proposed) (- (missionaries-right state) 2))
                 (setf (missionaries-left proposed) (+ (missionaries-left state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) ))))
            ((and (eql (boat-position state) 'L) (> (missionaries-left state) 1))
             (let ((proposed (copy-state state)))
                (write "I AM LEFT")
                (setf (missionaries-left proposed) (- (missionaries-left state) 2))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 2))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) )))))
                    (write "FINAL POSITION:  ")(write (boat-position state))(terpri)
                )

;; action that takes two cannibals
(defun take-two-cannibals (state)
    (write "take-two-cannibals")
    ;; (terpri)
    (cond   ((and (eql (boat-position state) 'R) (> (cannibals-right state) 1)) 
            (let ((proposed (copy-state state)))
                (write "I AM RIGHT")
                 (setf (cannibals-right proposed) (- (cannibals-right state) 2))
                 (setf (cannibals-left proposed) (+ (cannibals-left state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) ))))

            ((and (eql (boat-position state) 'L) (> (cannibals-left state) 1))
            (let ((proposed (copy-state state)))
                (write "I AM LEFT")
                 (setf (cannibals-left proposed) (- (cannibals-left state) 2))
                 (setf (cannibals-right proposed) (+ (cannibals-right state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 
                 (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) )))))
                 (write "FINAL POSITION:  ")(write (boat-position state))(terpri))

;; action that takes one missionary and one cannibal
(defun take-missionary-cannibal (state)

    (write (missionaries-right state))(terpri)
    (write (cannibals-right state))(terpri)

    (write "take-missionary-cannibal")
    ;; (terpri)
   (cond   ((and (eql (boat-position state) 'R) (and (>= (cannibals-right state) 1) (>= (missionaries-right state) 1) )) 
            (let ((proposed (copy-state state)))
                (write "I AM RIGHT")
                (setf (cannibals-right proposed) (- (cannibals-right state) 1))
                (setf (missionaries-right proposed) (- (missionaries-right state) 1))
                (setf (cannibals-left proposed) (+ (cannibals-left state) 1))
                (setf (missionaries-left proposed) (+ (missionaries-left state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) ))))
            ((and (eql (boat-position state) 'L) (and (>= (cannibals-left state) 1) (>= (missionaries-left state) 1)))
            (let ((proposed (copy-state state)))
                (write "I AM LEFT")
                (setf (cannibals-left proposed) (- (cannibals-left state) 1))
                (setf (missionaries-left proposed) (- (missionaries-left state) 1))
                (setf (cannibals-right proposed) (+ (cannibals-right state) 1))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                 
                (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) )))))
                (write "FINAL POSITION:  ")(write (boat-position state))(terpri))

;; Action that takes only one missionary
(defun take-one-missionary (state)
    (write "take-one-missionary")
    ;; (terpri)
    (cond   ((and (eql (boat-position state) 'R) (>= (missionaries-right state) 1)) 
            (let ((proposed (copy-state state)))
                (write "I AM RIGHT")
                (setf (missionaries-right proposed) (- (missionaries-right state) 1))
                (setf (missionaries-left proposed) (+ (missionaries-left state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) ))))
            ((and (eql (boat-position state) 'L) (>= (missionaries-left state) 1))
            (let ((proposed (copy-state state)))
            (write "I AM LEFT")
                (setf (missionaries-left proposed) (- (missionaries-left state) 1))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) )))))
                (write "FINAL POSITION:  ")(write (boat-position state))(terpri))

;; Action that takes only one cannibal
(defun take-one-cannibal (state)
    (write "take-one-cannibal")
    ;; (terpri)
    (cond   ((and (eql (boat-position state) 'R) (>= (cannibals-right state) 1)) 
            (let ((proposed (copy-state state)))
            (write "I AM RIGHT")
                 (setf (cannibals-right proposed) (- (cannibals-right state) 1))
                 (setf (cannibals-left proposed) (+ (cannibals-left state) 1))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 
                 (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) ))))
            ((and (eql (boat-position state) 'L) (>= (cannibals-left state) 1))
            (let ((proposed (copy-state state)))
            (write "I AM LEFT")
                 (setf (cannibals-left proposed) (- (cannibals-left state) 1))
                 (setf (cannibals-right proposed) (+ (cannibals-right state) 1))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 
                 (when (not (eql (safe proposed) nil))
                    (setf state ( copy-state proposed) )))))
                 (write "FINAL POSITION:  ")(write (boat-position state))(terpri))

(breadth-first-search  *missionaries-and-cannibals*) 