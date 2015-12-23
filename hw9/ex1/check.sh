#!/bin/bash
 x=`ps -ef | grep Run | awk '{print $3}'`
 for i in $x; 
 do
	 ps -ef | awk "{if (\"$i\" == \$2 && \$8 ~ /.*perf.*/) print \"found in
	 PID\", \$2; }"
done


