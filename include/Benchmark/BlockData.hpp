#ifndef BlockData_HPP
#define BlockData_HPP

#include "../Common/Maths.hpp"

namespace bmk {

class BlockData {
   private:
    std::string m_name;
    std::string m_file;
    int m_line;

   public:
    BlockData(std::string name, std::string file, int line);
    ~BlockData();
    std::string get_name();
    std::string get_file();
    int get_line();
};

}  // namespace bmk

#endif