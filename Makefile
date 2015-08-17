
COMPILER			 = g++
OPTIMIZATION_OPT	 = -O0
OPTIONS				 = -g -ggdb  -pthread -std=c++11 -W -Wall -W -Wno-long-long -lrt $(OPTIMIZATION_OPT)
LINKER_OPT			 = -L/usr/lib -lstdc++
#VEC_FLAGS			 = -msse2 -msse4.1 -mpclmul
#PROBE_T			 = 256

PREDEF				 = -D
OUT_DIR 			 = ./bin/

FCM_DIR 			 = ./fcm
KPP_DIR 			 = ./kpp
VANILLA_DIR			 = ./vanilla
HIERARCHICAL_DIR 	 = ./hierarchical


DEP = data.hh algorithm.hh

# Fuzzy C-means
DC_FCM 	= data.cc algorithm.cc ./algorithms/fcm/fcm.cc ./algorithms/fcm/runfcm.cc
#

# K-means++
DC_KPP 	= data.cc algorithm.cc ./algorithms/kpp/kpp.cc ./algorithms/kpp/runkpp.cc
#

# Vanilla K-means
DC_VANILLA 	= data.cc algorithm.cc ./algorithms/vanilla/vanilla.cc ./algorithms/vanilla/runvanilla.cc
#

# Hierarchical
DC_HIERARCHICAL	 = data.cc algorithm.cc ./algorithms/hierarchical/hierarchical.cc ./algorithms/hierarchical/runhierarchical.cc
#

#BUILD += FCM
BUILD += KPP
#BUILD += VANILLA
#BUILD += HIERARCHICAL


all: $(BUILD)

FCM: $(DEP) ./algorithms/fcm/fcm.hh
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)fcm $(DC_FCM) $(LINKER_OPT) $(DEFINE_1)

KPP: $(DEP) ./algorithms/kpp/kpp.hh
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)kpp $(DC_KPP) $(LINKER_OPT) $(DEFINE_2)

VANILLA: $(DEP) ./algorithms/vanilla/vanilla.hh
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)vanilla $(DC_VANILLA) $(LINKER_OPT) $(DEFINE_3)

HIERARCHICAL: $(DEP) ./algorithms/hierarchical/hierarchical.hh
	$(COMPILER) $(OPTIONS) -o $(OUT_DIR)hierarchical $(DC_HIERARCHICAL) $(LINKER_OPT) $(DEFINE_4)

clean:
	rm -rf ./bin/fcm ./bin/hierarchical ./bin/kpp ./bin/vanilla
#
# The End !
#
