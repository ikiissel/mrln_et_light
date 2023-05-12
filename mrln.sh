#!/bin/bash -e

#panin igaks juhuks, äkki on abiks#
eval "$(conda shell.bash hook)"
conda activate mrln_et
###################################

merlin_dir=$(pwd)
temp_dir=/home/indrek/mrln_et_light/temp
voice=eki_et_tnu16k
in_text=/home/indrek/mrln_et_light/in.txt
out_wav=/home/indrek/mrln_et_light/out.wav

echo "synthesizing ..."
python ${merlin_dir}/src/run_merlin.py ${merlin_dir} ${temp_dir} ${voice} ${in_text} ${out_wav}
echo "done"
