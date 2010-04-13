#ifndef __MinimalParser__
#define __MinimalParser__

#include <vector>

#include "TNamed.h"
#include "TString.h"


// Shortcuts -------------------------------------------------------------------

typedef std::vector<TString> vString;
typedef std::vector<double> vdouble;
typedef std::vector<int> vint;

//------------------------------------------------------------------------------

class MinimalParser : public TNamed {

  public:

    /// The default  ctor
    MinimalParser(){};

    /// The constructor
    MinimalParser (const char* cardname);

    /// Set Verbosity
    void setVerbose(bool value){m_is_verbose=value;};

    /// Is parameter there?
    bool has(const char* namesec);

    /// Read parameter as a integer
    bool read (const char* section_name, const char* par_name, int& val);

    /// Return read integer
    int getInt (const char* namesec);

    /// Return read vector of integers
    std::vector<int> getvInt (const char* namesec);

    /// Return read double
    double getDouble (const char* namesec);

    /// Return read vector of doubles
    std::vector<double> getvDouble (const char* namesec);

    /// Return read string
    TString getString (const char* namesec,const char* def_val=0);

    /// Return read vector of strings
    std::vector<TString> getvString (const char* namesec);

    /// Read parameter as a int vector
    bool read (const char* section_name, 
               const char* par_name, 
               std::vector<int>& val);

    /// Read parameter as a double
    bool read (const char* section_name, const char* par_name, double& val);

    /// Read parameter as a double vector
    bool read (const char* section_name,
               const char* par_name,
               std::vector<double>& val);

    /// Read parameter as a string
    bool read (const char* section_name,
               const char* par_name,
               TString& val,
               bool numeric_conversion=false);

    /// Read parameter as a string vector
    bool read (const char* section_name, 
               const char* par_name, 
               std::vector<TString>& val,
               bool numeric_conversion=false);

    /// Get the sections list
    vString getSections(){return m_sections;};

    /// Get the sections list size
    int getSectionsNum(){return m_sections.size();};



  private:

    /// The Config name
    TString m_cfg_name;

    /// Verbosity value
    bool m_is_verbose;

    /// Print error message
    void m_print_error(const char* par_name,
                       const char* sec_name,
                       const char* config_name);

    /// Convert string to double or seek for symbol in cfg
    double m_read_double(TString& val);

    /// Separate section and parameter
    void m_split_sec_par(const char* secpar,
                         TString& sec,
                         TString& par);

    /// The section list
    vString m_sections;

    // For Cint
    ClassDef(MinimalParser,1)
 };

#endif
