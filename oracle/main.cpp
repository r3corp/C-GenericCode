#include <iostream>
//#include <Oracle.h>
#include <vector>

using namespace std;

typedef void(*ICONNECT_ERRORPROC)(const char *);

class COracle{
public:
    COracle(ICONNECT_ERRORPROC=NULL){}
    bool Open(const char *) {}
    int GetFieldCount() {}
    const char* GetFieldName(int index) {}
    const char* GetFieldValue(int index) {}
    void MoveNext () {}
    bool IsEOF() {}
};

void connectErrorMsg(const char* c){
    printf("%s", c);
}
int main() {

    COracle * instanceOracleProvider = new COracle(connectErrorMsg); //not much into fp but...
    //COracle * instanceOracleProvider = new COracle([](const char * errorMsg) { cout << errorMsg; }); //not much into fp but...
    std::vector<string*> storage;
    if (!instanceOracleProvider->Open("select a.object_id, a.author, a.title from testing a where a.author =‘iconect\\london’ or a.object_id >= 5"))
    {
        printf("no good.... no result");

    }else{
        int fieldCount = instanceOracleProvider->GetFieldCount(); //the field count shouldn't change...
        bool headerLineFilled = false;
        while(!instanceOracleProvider->IsEOF()){
            //read through till the end
            string *stringToAdd;
            if (!headerLineFilled) {
                //creating comma separated line with header fields
                stringToAdd = new string();
                stringToAdd->append(string(instanceOracleProvider->GetFieldName(0)));
                for (int index = 1; index < fieldCount; index++) {
                    //reading field names
                    stringToAdd->append(",");
                    stringToAdd->append(string(instanceOracleProvider->GetFieldName(index)));
                }
                storage.push_back(stringToAdd);
            }
            //creating comma separated lines with values
            stringToAdd = new string();
            stringToAdd->append(string(instanceOracleProvider->GetFieldValue(0)));
            for (int index = 1; index < fieldCount; index++) {
                stringToAdd->append(",");
                stringToAdd->append(string(instanceOracleProvider->GetFieldValue(index)));
            }
            storage.push_back(stringToAdd);
            delete stringToAdd;
            headerLineFilled=true;
            instanceOracleProvider->MoveNext();
        }
    }
    for (int i =0 ; i < storage.size(); i++)
        delete storage[i];
    delete instanceOracleProvider; //removing the instance

    return 0;
}
