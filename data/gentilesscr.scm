#!/usr/bin/guile \
-e main -s
!#

(load "helper.scm")

(define (get-images-lst)
  (filter (lambda (filename)
	    (equal? (stat:type (stat (string-append "images/tiles/" filename))) 'regular))
	  (directory->list "images/tiles/")))

(define (main args)
  (println "<resources>")
  (println "<section name=\"tiles\">")
  (for-each (lambda (filename)
	      (println "	<sprite name=\"" (substring filename 0 (- (string-length filename) 4)) "\">\n" 
		       "  <image name=\"image1\" file=\"images/tiles/" filename "\" />"
                       " </sprite>\n")
              )
	    (sort (get-images-lst) string<=?))
  (println "</section>\n"
           " </resources>\n")
  (newline))

;; EOF ;;