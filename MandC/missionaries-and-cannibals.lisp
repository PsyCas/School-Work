;;; Solves the Missionaries and Cannibals using breadth first search.
;;; Output Answer: TAKE-2-CANNIBALS TAKE-1-CANNIBAL TAKE-2-CANNIBALS TAKE-1-CANNIBAL TAKE-2-MISSIONARIES TAKE-MISSIONARY-CANNIBAL TAKE-2-MISSIONARIES TAKE-1-CANNIBAL TAKE-2-CANNIBALS TAKE-1-MISSIONARY TAKE-MISSIONARY-CANNIBAL
;;; TAKE-2-CANNIBALS: Take 2 cannibals from the side the boat is currently on.
;;; TAKE-2-MISSIONARIES: Take 2 missionaries from the side the boat is currently on.
;;; TAKE-MISSIONARY-CANNIBAL: Take 1 missionary and 1 cannibal from the side the boat is currently on.
;;; TAKE-MISSIONARY: Take 1 missionary from the side the boat is currently on.
;;; TAKE-CANNIBAL: Take 1 cannibal from the side the boat is currently on.


;; Defines the state of the two shores at any given time
(defclass game-state (state)
    ((missionaries-right :initarg :missionaries-right :initform nil :accessor missionaries-right :documentation "Number of missionaries on the right shore.")
     (missionaries-left :initarg :missionaries-left :initform nil :accessor missionaries-left :documentation "Number of missionaries on the left shore.")
     (cannibals-right :initarg :cannibals-right :initform nil :accessor cannibals-right :documentation "Number of cannibals on the right shore.")
     (cannibals-left :initarg :cannibals-left :initform nil :accessor cannibals-left :documentation "Number of cannibals on the left shore.")
     (boat-position :initarg :boat-position :initform nil :accessor boat-position :documentation "Number of cannibals on the boat." )))

;; Defines the problem with actions and goal state 
(defparameter *missionaries-and-cannibals* 
  (make-instance 'problem 
    :start-state (make-instance 'game-state :missionaries-right 3 :missionaries-left 0 :cannibals-right 3 :cannibals-left 0 :boat-position 'R)
    :goal-test 'all-on-leftp
    :operators '(take-2-missionaries take-2-cannibals take-missionary-cannibal take-1-missionary take-1-cannibal)
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

;; checking the state for safe moves
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
    (cond ((eql side 'L) 'R)
          ((eql side 'R) 'L))) 

;; Action that transfers two missionaries on the boat
(defun take-2-missionaries (state)
    (cond   ((and (eql (boat-position state) 'R) (> (missionaries-right state) 1))      ; if the boat is on the right
             (let ((proposed (copy-state state))) 
                 (setf (missionaries-right proposed) (- (missionaries-right state) 2))
                 (setf (missionaries-left proposed) (+ (missionaries-left state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 (safe proposed))) 
            ((and (eql (boat-position state) 'L) (> (missionaries-left state) 1))       ; if the boat is on the left
             (let ((proposed (copy-state state)))
                (setf (missionaries-left proposed) (- (missionaries-left state) 2))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 2))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))))

;; Action that transfers two cannibals on the boat
(defun take-2-cannibals (state)
    (cond   ((and (eql (boat-position state) 'R) (> (cannibals-right state) 1))         ; if the boat is on the right
            (let ((proposed (copy-state state)))
                 (setf (cannibals-right proposed) (- (cannibals-right state) 2))
                 (setf (cannibals-left proposed) (+ (cannibals-left state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 (safe proposed)))

            ((and (eql (boat-position state) 'L) (> (cannibals-left state) 1))          ; if the boat is on the left
            (let ((proposed (copy-state state)))
                 (setf (cannibals-left proposed) (- (cannibals-left state) 2))
                 (setf (cannibals-right proposed) (+ (cannibals-right state) 2))
                 (setf (boat-position proposed) (move-boat (boat-position state)))                 
                 (safe proposed)))))

;; Action that trasnfers one missionary and one cannibal on the boat
(defun take-missionary-cannibal (state)
   (cond   ((and (eql (boat-position state) 'R) (and (>= (cannibals-right state) 1) (>= (missionaries-right state) 1))) ; if the boat is on the right 
            (let ((proposed (copy-state state)))
                (setf (cannibals-right proposed) (- (cannibals-right state) 1))
                (setf (missionaries-right proposed) (- (missionaries-right state) 1))
                (setf (cannibals-left proposed) (+ (cannibals-left state) 1))
                (setf (missionaries-left proposed) (+ (missionaries-left state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))
            ((and (eql (boat-position state) 'L) (and (>= (cannibals-left state) 1) (>= (missionaries-left state) 1))) ; if the boat is on the left
            (let ((proposed (copy-state state)))
                (setf (cannibals-left proposed) (- (cannibals-left state) 1))
                (setf (missionaries-left proposed) (- (missionaries-left state) 1))
                (setf (cannibals-right proposed) (+ (cannibals-right state) 1))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))))

;; Action that trasnfers only one missionary 
(defun take-1-missionary (state)
    (cond   ((and (eql (boat-position state) 'R) (>= (missionaries-right state) 1))     ; if the boat is on the right
            (let ((proposed (copy-state state)))
                (setf (missionaries-right proposed) (- (missionaries-right state) 1))
                (setf (missionaries-left proposed) (+ (missionaries-left state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))
            ((and (eql (boat-position state) 'L) (>= (missionaries-left state) 1))      ; if the boat is on the left
            (let ((proposed (copy-state state)))
                (setf (missionaries-left proposed) (- (missionaries-left state) 1))
                (setf (missionaries-right proposed) (+ (missionaries-right state) 1))
                (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))))

;; Action that transfers only one cannibal
(defun take-1-cannibal (state)
    (cond   ((and (eql (boat-position state) 'R) (>= (cannibals-right state) 1))    ; if the boat is on the right
            (let ((proposed (copy-state state)))
                 (setf (cannibals-right proposed) (- (cannibals-right state) 1))
                 (setf (cannibals-left proposed) (+ (cannibals-left state) 1))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                 (safe proposed)))
            ((and (eql (boat-position state) 'L) (>= (cannibals-left state) 1))     ; if the boat is on the left
            (let ((proposed (copy-state state)))
                 (setf (cannibals-left proposed) (- (cannibals-left state) 1))
                 (setf (cannibals-right proposed) (+ (cannibals-right state) 1))
                 (setf (boat-position proposed) (move-boat (boat-position state)))
                (safe proposed)))))

(breadth-first-search  *missionaries-and-cannibals*) 
