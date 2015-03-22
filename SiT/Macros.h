#define NS_SIT_BEGIN                     namespace SiT {
#define NS_SIT_END                       }
#define USING_NS_SIT                     using namespace SiT;

//#if defined(_USRDLL)
//    #define SIT_DLL     __declspec(dllexport)
//#else         /* use a DLL library */
//    #define SIT_DLL     __declspec(dllimport)
//#endif

#define SIT_DLL

void log(const char * format, ...);

#define LOG(format, ...) log(format, ##__VA_ARGS__);
#define MAX_LOG_LENGTH 1000

#define PI 3.14159265358979323846

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)