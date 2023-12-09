#include <iostream>

using namespace std;

typedef struct elmTrain *adrTrain;
typedef struct elmStation *adrStation;
typedef struct elmGarage *adrGarage;

struct train {
  string jadwal,

};

struct garage {

};

struct station {

};

struct elmTrain {
  train infoTrain;
  adrTrain nextTrain;
};

struct elmStation {
  station infoStation;
  adrStation nextStation;
};

struct elmGarage {
  garage infoGarage;
  adrGarage nextGarage;
};

struct listTrain {
  adrTrain first;
};

struct listStation {
  adrStation first;
};

struct listGarage {
  adrGarage first;
};