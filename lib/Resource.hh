// TODO - Documentation

#ifndef __Resource_hh
#define __Resource_hh

#include <string>

// forward declaration
typedef struct _XrmHashBucketRec *XrmDatabase;


namespace bt {

  inline const char* boolAsString(bool b)
  { return (b) ? "True" : "False"; }

  class Resource {
  public:
    Resource(void);
    explicit Resource(const std::string &filename);
    ~Resource(void);

    inline bool valid(void) const
    { return db != NULL; }

    void load(const std::string &filename);
    void save(const std::string &filename);
    void merge(const std::string &filename);

    std::string read(const char* name,
                     const char* classname,
                     const char* default_value = "") const;
    std::string read(const std::string &name,
                     const std::string &classname,
                     const std::string &default_value = std::string()) const;

    int read(const char* name, const char* classname,
             int default_value) const;
    unsigned int read(const char* name, const char* classname,
                      unsigned int default_value) const;

    long read(const char* name, const char* classname,
              long default_value) const;
    unsigned long read(const char* name, const char* classname,
                       unsigned long default_value) const;

    bool read(const char* name, const char* classname,
              bool default_value) const;

    double read(const char* name, const char* classname,
                double default_value) const;

    void write(const char *resource, const std::string &value);
    void write(const char* resource, const char* value);
    void write(const char* resource, int value);
    void write(const char* resource, unsigned int value);
    void write(const char* resource, long value);
    void write(const char* resource, unsigned long value);
    void write(const char* resource, bool value);
    void write(const char* resource, double value);

  private:
    XrmDatabase db;
  };

} // namespace bt

#endif // __Resource_hh
