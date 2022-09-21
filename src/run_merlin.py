################################################################################
#           The Neural Network (NN) based Speech Synthesis System
#                https://github.com/CSTR-Edinburgh/merlin
#
#                Centre for Speech Technology Research
#                     University of Edinburgh, UK
#                      Copyright (c) 2014-2015
#                        All Rights Reserved.
#
# The system as a whole and most of the files in it are distributed
# under the following copyright and conditions
#
#  Permission is hereby granted, free of charge, to use and distribute
#  this software and its documentation without restriction, including
#  without limitation the rights to use, copy, modify, merge, publish,
#  distribute, sublicense, and/or sell copies of this work, and to
#  permit persons to whom this work is furnished to do so, subject to
#  the following conditions:
#
#   - Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   - Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#   - The authors' names may not be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK
#  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
#  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT
#  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE
#  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
#  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
#  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
#  THIS SOFTWARE.
################################################################################

import pickle
import os, sys, errno
import numpy.distutils.__config__

from frontend.label_normalisation import HTSLabelNormalisation
from frontend.silence_remover import SilenceRemover
from frontend.min_max_norm import MinMaxNormalisation
from frontend.parameter_generation import ParameterGeneration
from frontend.mean_variance_norm import MeanVarianceNorm
from frontend.label_modifier import HTSLabelModification

from utils.generate import generate_wav
from utils.generate import run_process #vajalik labelite genereerimiseks


def Read_file_list(file_name):

  file_lists = []
  fid = open(file_name)
  for line in fid.readlines():
    line = line.strip()
    if len(line) < 1:
      continue
    file_lists.append(line)
  fid.close()

  #print('Read file list from %s', file_name)
  return file_lists


def prepare_file_path_list(file_id_list,
                           file_dir,
                           file_extension,
                           new_dir_switch=True):
  #logger = logging.getLogger('prepare_file_path_list')

  if not os.path.exists(file_dir) and new_dir_switch:
    os.makedirs(file_dir)

  #print ('Preparing file_list', file_extension, file_dir)

  return [
      os.path.join(file_dir, file_id + file_extension)
      for file_id in file_id_list
  ]





# VAJALIK, käib läbi nii dur kui acou
def dnn_generation(valid_file_list, nnets_file_name, n_ins, n_outs, out_file_list):

    dnn_model = pickle.load(open(nnets_file_name, 'rb'))
    file_number = len(valid_file_list)

    for i in range(file_number):  #file_number
        fid_lab = open(valid_file_list[i], 'rb')
        features = numpy.fromfile(fid_lab, dtype=numpy.float32)
        fid_lab.close()
        features = features[:(n_ins * (features.size // n_ins))]
        test_set_x = features.reshape((-1, n_ins))
        n_rows = test_set_x.shape[0]
        

        predicted_parameter = dnn_model.parameter_prediction(test_set_x)
        predicted_parameter = predicted_parameter.reshape(-1, n_outs)
        predicted_parameter = predicted_parameter[0:n_rows]
        
        ### write to cmp file
        predicted_parameter = numpy.array(predicted_parameter, 'float32')
        temp_parameter = predicted_parameter
        fid = open(out_file_list[i], 'wb')
        predicted_parameter.tofile(fid)
        fid.close()




def main_function(AcousticModel, full_path_dir, TempDir, voice_name):

    #print()

    #*************************** Parameetrid ******************************
    # constid, mis peaks tulema main_function parameetrina
    #full_path_dir = "/home/indrek/disk2/mrln_et_light/"
    TempDir = TempDir + "/" # ei ole ilus
    SPTKBinDir = full_path_dir + "/tools/bin/SPTK-3.9"
    WorldBinDir = full_path_dir + "/tools/bin/WORLD"
    #voice_name = "eki_et_tnu16k"        

    #eeldab test_id_list.scp asub temp kataloogi juurikas
    TestIdList = Read_file_list(TempDir + "test_id_list.scp")
    #***********************************************************************
    
    voice_dir = full_path_dir + "/voices/" + voice_name + "/"
    question_file_name = full_path_dir + "/src/qst008.hed"
    add_feat_dim = 0
    LabelType = "state_align"
    SilencePattern = ['*-brth+*']
    min_value = 0.01
    max_value = 0.99
    DurExt = '.dur'
    LabExt = '.lab'
    # Siit osad välja korjata
    FileExtensionDict = {'mgc': '.mgc', 'lf0': '.lf0', 'bap': '.bap', 'stepw': '.stepw', 'cmp': '.cmp', 'seglf0': '.lf0', 'dur': '.dur'}

    # Mõlemad wav_gen-i jaoks    
    SPTK = {
            'X2X'    : os.path.join(SPTKBinDir,'x2x'),
            'MERGE'  : os.path.join(SPTKBinDir,'merge'),
            'BCP'    : os.path.join(SPTKBinDir,'bcp'),
            'MLPG'   : os.path.join(SPTKBinDir,'mlpg'),
            'MGC2SP' : os.path.join(SPTKBinDir,'mgc2sp'),
            'VSUM'   : os.path.join(SPTKBinDir,'vsum'),
            'VSTAT'  : os.path.join(SPTKBinDir,'vstat'),
            'SOPR'   : os.path.join(SPTKBinDir,'sopr'),
            'VOPR'   : os.path.join(SPTKBinDir,'vopr'),
            'FREQT'  : os.path.join(SPTKBinDir,'freqt'),
            'C2ACR'  : os.path.join(SPTKBinDir,'c2acr'),
            'MC2B'   : os.path.join(SPTKBinDir,'mc2b'),
            'B2MC'   : os.path.join(SPTKBinDir,'b2mc')
    }

    WORLD = {
            'SYNTHESIS'     : os.path.join(WorldBinDir, 'synth'),
            'ANALYSIS'      : os.path.join(WorldBinDir, 'analysis'),
    }



    
    if AcousticModel:
        model_type = "acoustic_model/"
        add_frame_features = True
        subphone_feats = "full"
        lab_dim = 369 #kas on constant, ei tea? On sõltuvuses qst-st ja muutub. Tundub et acou on alati dur + 9
        remove_frame_features = True
        lab_dir = TempDir + "gen-lab"
        gen_dir = TempDir + "wav"
        FeatureNameList = ['mgc', 'lf0', 'vuv', 'bap']
        FeatureFileList = ['mgc_180', 'lf0_3', 'vuv_1', 'bap_3']
        NormInfoFileName = "norm_info__mgc_lf0_vuv_bap_187_MVN.dat"
        CmpDim = 187
        GenWavFeatures = ['mgc', 'lf0', 'bap']
        OutDimensionDict = {'mgc': 180, 'lf0': 3, 'vuv': 1, 'bap': 3}
    else:
        model_type = "duration_model/";
        add_frame_features=False
        subphone_feats="none"
        lab_dim = 360 #kas on constant, ei tea?
        remove_frame_features = False
        lab_dir = TempDir + "prompt-lab"
        gen_dir = TempDir + "gen-lab"
        FeatureNameList = ['dur']
        FeatureFileList = ['dur_5']
        NormInfoFileName = "norm_info__dur_5_MVN.dat"
        CmpDim = 5
        GenWavFeatures = ['mgc', 'bap', 'lf0']
        OutDimensionDict = {'dur': 5}

    model_dir = voice_dir + model_type + "nnets_model"
    label_norm_file = voice_dir + model_type + "inter_module/label_norm_HTS_" + str(lab_dim) + ".dat"
    NormInfoFile = voice_dir + model_type + "inter_module/" + NormInfoFileName
    min_max_normaliser = None
    
    in_label_align_file_list = prepare_file_path_list(TestIdList, lab_dir, ".lab", True)
    binary_label_file_list   = prepare_file_path_list(TestIdList, gen_dir, ".labbin", True)
    nn_label_file_list       = prepare_file_path_list(TestIdList, gen_dir, ".lab", True)    

		# Loll formaat, aga on kasutuses [x: 'y', jne]
    x = 0
    VarFileDict = {}
    for FeatureName in FeatureNameList:
        s = voice_dir + model_type + "inter_module/var/" + FeatureFileList[x]
        VarFileDict[FeatureName] = s
        x = x + 1

    NnetsFileName = voice_dir + model_type + "nnets_model/feed_forward_6_tanh.model"

    try:
        os.makedirs(gen_dir)
    except OSError as e:
        if e.errno == errno.EEXIST:
            pass
        else:
           print('Failed to create generation directory %s' % gen_dir)
           raise
		
    if True: # Sest ei viitsi neid tühikuid paika ajada
        # simple HTS labels        
        label_normaliser = HTSLabelNormalisation(question_file_name, add_frame_features, subphone_feats)        
        label_normaliser.perform_normalisation(in_label_align_file_list, binary_label_file_list, LabelType)

        remover = SilenceRemover(lab_dim, SilencePattern, LabelType, remove_frame_features, subphone_feats)
        remover.remove_silence(binary_label_file_list, in_label_align_file_list, nn_label_file_list)

        min_max_normaliser = MinMaxNormalisation(lab_dim, min_value, max_value)
        min_max_normaliser.load_min_max_values(label_norm_file)

        ### enforce silence such that the normalization runs without removing silence: only for final synthesis
        #if cfg.GenTestList and cfg.enforce_silence:
        if AcousticModel: 
            min_max_normaliser.normalise_data(binary_label_file_list, nn_label_file_list)
        else:
            min_max_normaliser.normalise_data(nn_label_file_list, nn_label_file_list)
        # ******************** Normaliseerimise lõpp **************************************
        
        gen_file_list = prepare_file_path_list(TestIdList, gen_dir, '.cmp')

        dnn_generation(nn_label_file_list, NnetsFileName, lab_dim, CmpDim, gen_file_list)
        #
        #print('denormalising generated output using method %s' % cfg.output_feature_normalisation)
        #norm_info_file = file_paths.norm_info_file
        
        fid = open(NormInfoFile, 'rb')
        cmp_min_max = numpy.fromfile(fid, dtype=numpy.float32)
        fid.close()
        cmp_min_max = cmp_min_max.reshape((2, -1))
        cmp_min_vector = cmp_min_max[0, ]
        cmp_max_vector = cmp_min_max[1, ]


        #output_feature_normalisation == 'MVN'
        denormaliser = MeanVarianceNorm(feature_dimension = CmpDim)
        denormaliser.feature_denormalisation(gen_file_list, gen_file_list, cmp_min_vector, cmp_max_vector)

        if AcousticModel:
            ##perform MLPG to smooth parameter trajectory
            ## lf0 is included, the output features much have vuv.
            generator = ParameterGeneration(gen_wav_features = GenWavFeatures, enforce_silence = True)
            generator.acoustic_decomposition(gen_file_list, CmpDim, OutDimensionDict, FileExtensionDict, VarFileDict, SilencePattern, lab_dir, do_MLPG=True)
            generate_wav(gen_dir, TestIdList, SPTK, WORLD)

        else:
            ### Perform duration normalization(min. state dur set to 1) ###
            gen_dur_list   = prepare_file_path_list(TestIdList, gen_dir, DurExt)
            gen_label_list = prepare_file_path_list(TestIdList, gen_dir, LabExt)
            in_gen_label_align_file_list = prepare_file_path_list(TestIdList, lab_dir, LabExt, False)

            generator = ParameterGeneration(gen_wav_features = GenWavFeatures)
            generator.duration_decomposition(gen_file_list, CmpDim, OutDimensionDict, FileExtensionDict)
            
            #cmp + dur + lab(bin) + binlab = lab(aegadega)
            label_modifier = HTSLabelModification(silence_pattern = SilencePattern, label_type = LabelType)
            label_modifier.modify_duration_labels(in_gen_label_align_file_list, gen_dur_list, gen_label_list)            



if __name__ == '__main__':

    # create a configuration instance
    # and get a short name for this instance
    #cfg=configuration.cfg


    #if len(sys.argv) != 2:
        ##print('usage: run_merlin.sh [config file name]')
        #sys.exit(1)



    full_path_dir = sys.argv[1]
    TempDir = sys.argv[2]
    voice_name = sys.argv[3]
    in_text = sys.argv[4]
    out_wav = sys.argv[5]

    run_process("mkdir -p " + TempDir + "/prompt-lab")    
    run_process("rm -f " + TempDir + "/gen-lab/*.*")
    run_process("rm -f " + TempDir + "/wav/*.*")
    run_process("rm -f " + TempDir + "/prompt-lab/*.*")
    
    genlab_dir = full_path_dir + "/tools/genlab/"
    t = genlab_dir + "bin/genlab -lex " + genlab_dir + "dct/et.dct -lexd " + genlab_dir + "dct/et3.dct -o " + TempDir + "/ -f " + in_text
    run_process(t)        
#    sys.exit(1)

    
    
    
    #config_file = os.path.abspath(config_file)
    #cfg.configure(config_file)
    AcousticModel = False
    main_function(AcousticModel, full_path_dir, TempDir, voice_name)
    AcousticModel = True
    main_function(AcousticModel, full_path_dir, TempDir, voice_name)
    
    run_process("sox " + TempDir + "/wav/*.wav " + out_wav)

    sys.exit(0)
    
