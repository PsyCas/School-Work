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
