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

(defun record-by-dob-p (r1 r2)
  (< (getf r1 :dob) (getf r2 :dob)))

(defun record-by-birthday-p (r1 r2)
  " Predicate that sorts by birthday (i.e. month and day) "
  (let ((d1 (decode-date (getf r1 :dob)))
	(d2 (decode-date (getf r2 :dob))))
    (if (equal (getf d1 :month) (getf d2 :month))
	(< (getf d1 :day) (getf d2 :day))
     (< (getf d1 :month) (getf d2 :month)))))

(defun dump-db (database)
  (dolist (record database)
    (format t "~a: ~10t~a~%" (getf record :name) (stringify-date (getf record :dob)))))

(defun dump-db-sort-by-dob (database)
  (dump-db (sort database 'record-by-dob-p)))

(defun dump-db-sort-by-bday (database)
  (dump-db (sort database 'record-by-birthday-p)))

(defun save-db (filename)
  (with-open-file (out filename
		       :direction :output
		       :if-exists :supersede)
    (with-standard-io-syntax (print *db* out))))

(defun load-db (filename)
  (with-open-file (in filename)
    (with-standard-io-syntax (setf *db* (read in)))))

(defun clear-db ()
  (setq *db* nil))
