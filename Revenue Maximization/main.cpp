#include <stdlib.h>
#include "time.h"
#include "utilityfunction.h"
#include "OneStream.h"
#include "SmkStream.h"
#include "MultiStream.h"
#include "DynamicMRT.h"
int main(int argc,char *argv[]) {
    //random_weight();
    //random_cost();
    //renum();
    //cumulate_normalize_cost(0.2);

    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    read_data();
    string::size_type pos1, pos2,posend;
    pos1=node_cost_text.find_last_of("/");
    pos2=node_cost_text.rfind("/",pos1-1);

    posend=node_cost_text.find_last_not_of("/");
    string name1=node_cost_text.substr(pos2+1,pos1-pos2-1);
    string name2=node_cost_text.substr(pos1+1,posend);
    string result_name=name1+"_"+name2;
    //cout<<result_name<<endl;
    string outtext="./result/result_"+result_name+"_"+to_string(p->tm_mon+1)+"."+to_string(p->tm_mday)+"_"+to_string(p->tm_hour)+"_"+to_string(p->tm_min)+"_"+to_string(p->tm_sec)+".txt";


//    double B=atof(argv[1]);
 //   double B_ratio=atof(argv[1]);
    //double eps=atof(argv[2]);
    double eps=0.1;
    cout<<"eps: "<<eps<<endl;

    vector<Result> onestream_result;
    vector<Result> multistream_result;
    vector<Result> smkstream_result;
    vector<Result> DMRT_result;

    vector<Result> multiplexgreedy_result;
    vector<Result> matknapstream_result;

    double B_start=100.0;
    double B_end=200.0;
    double B_step=10.0;
    for(double B=B_start;B<=B_end;B+=B_step)
    {
        cout<<"Budget: "<<B<<endl;
        onestream_result.emplace_back(OneStream(B,eps));
        multistream_result.emplace_back(MultiStream(B,eps));
        smkstream_result.emplace_back(SmkStream(B,eps));
        DMRT_result.emplace_back(DynamicMRT(B,eps));
    }


    ofstream out(outtext);
    out<<"eps: "<<eps<<endl;
    //out<<"real Budget: "<<endl;
    for(double B=B_start;B<=B_end;B+=B_step)
    {
        out<<B<<"\t";
    }
    out<<endl;

   out<<"OneStream "<<endl;
    out<<"utility: "<<endl;
    for(auto p:onestream_result)
    {
        out<<p.revenue<<"\t";
    }
    out<<endl;
    out<<"query: "<<endl;
    for(auto p:onestream_result)
    {
        out<<p.oracle<<"\t";
    }
    out<<endl;
    out<<"memory: "<<endl;
    for(auto p:onestream_result)
    {
        out<<p.memory<<"\t";
    }
    out<<endl;

    out<<"MultiStream "<<endl;
    out<<"utility: "<<endl;
    for(auto p:multistream_result)
    {
        out<<p.revenue<<"\t";
    }
    out<<endl;
    out<<"query: "<<endl;
    for(auto p:multistream_result)
    {
        out<<p.oracle<<"\t";
    }
    out<<endl;
    out<<"memory: "<<endl;
    for(auto p:multistream_result)
    {
        out<<p.memory<<"\t";
    }
    out<<endl;


    out<<"SmkStream "<<endl;
    out<<"utility: "<<endl;
    for(auto p:smkstream_result)
    {
        out<<p.revenue<<"\t";
    }
    out<<endl;
    out<<"query: "<<endl;
    for(auto p:smkstream_result)
    {
        out<<p.oracle<<"\t";
    }
    out<<endl;
    out<<"memory: "<<endl;
    for(auto p:smkstream_result)
    {
        out<<p.memory<<"\t";
    }
    out<<endl;

    out<<"DynamicMRT "<<endl;
    out<<"utility: "<<endl;
    for(auto p:DMRT_result)
    {
        out<<p.revenue<<"\t";
    }
    out<<endl;
    out<<"query: "<<endl;
    for(auto p:DMRT_result)
    {
        out<<p.oracle<<"\t";
    }
    out<<endl;
    out<<"memory: "<<endl;
    for(auto p:DMRT_result)
    {
        out<<p.memory<<"\t";
    }
    out<<endl;


    return 0;
}
