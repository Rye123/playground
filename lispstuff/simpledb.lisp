(defvar *db* nil)

;;; Date Functions
(defun encode-date (year month day)
  " Encodes a date into an integer timestamp "
  (encode-universal-time 0 0 0 day month year))

(defun decode-date (timestamp)
  " Decodes an integer timestamp into a year, month and day list "
  (let ((dt nil))
    (setq dt (multiple-value-list (decode-universal-time timestamp)))
    (list :year (nth 5 dt) :month (nth 4 dt) :day (nth 3 dt))))

(defun stringify-date (timestamp)
  " Returns a string representing the date (YYYY-MM-DD) based on the timestamp "
  (let ((date nil))
    (setq date (decode-date timestamp))
    (format nil "~d-~d-~d" (getf date :year) (getf date :month) (getf date :day))))

;; Record Functions
(defun add-record (name date)
  " Takes a name string and a date list (year, month, day), and stores it as a name and timestamp. "
  (push (list :name name :dob (apply 'encode-date date)) *db*))

(defun dump-db ()
  (dolist (record *db*)
    (format t "~a: ~10t~a~%" (getf record :name) (stringify-date (getf record :dob)))))
