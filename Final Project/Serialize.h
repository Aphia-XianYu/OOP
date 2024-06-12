#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <string>
#include<fstream>
#include <type_traits>
#include<typeinfo>
#include<tuple>


namespace XianYu_Serialize {
    class DataStream {
    public:
        enum DataType {
            BOOL = 0,
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
            SIZE_T,
            STRING,
            PAIR,
            VECTOR,
            LIST,
            MAP,
            SET,
        };

        DataStream() = default;
        ~DataStream() = default;

        void write(const char* data, int len);
        void write(bool value);
        void write(char value);
        void write(int value);
        void write(float value);
        void write(double value);
        void write(size_t value);
        void write(const char* value);
        void write(const std::string& value);
        
        template<typename T>
        void write(const T& value);
        template<typename T, typename U>
        void write(const std::pair<T, U>& value);
        template<typename T>
        void write(const std::vector<T>& value);
        template<typename T>
        void write(const std::list<T>& value);
        template<typename T, typename U>
        void write(const std::map<T, U>& value);
        template<typename T>
        void write(const std::set<T>& value);

        bool read(bool& value);
        bool read(char& value);
        bool read(int& value);
        bool read(double& value);
        bool read(float& value);
        bool read(size_t& value);
        bool read(std::string& value);

        template <typename T>
        bool read(T& value);
        template<typename T, typename U>
        bool read(std::pair<T, U>& value);
        template<typename T>
        bool read(std::vector<T>& value);
        template<typename T>
        bool read(std::list<T>& value);
        template<typename T, typename U>
        bool read(std::map<T, U>& value);
        template<typename T>
        bool read(std::set<T>& value);
        
        inline bool checkflag()const{ 
            return read_flag; 
        }

        template<typename T>
        DataStream& operator<<(const T& value);
        template<typename T>
        DataStream& operator>>(T& value);

        inline std::vector<char>& get_buf(){
            return m_buf;
        }

    private:

        std::vector<char> m_buf;
        void inflate(int len);
        int m_pos = 0;
        bool read_flag;

        

    };

    void DataStream::inflate(int len) {
        int size = m_buf.size();
        int cap = m_buf.capacity();
        if (size + len > cap) {
            while (size + len > cap) {
                cap = (cap == 0) ? 1 : cap * 2;
            }
            m_buf.reserve(cap);
        }
    }

    void DataStream::write(const char* data, int len) {
        inflate(len);
        int size = m_buf.size();
        m_buf.resize(static_cast<int>(size + len));
        std::memcpy(&m_buf[size], data, len);
    }
    void DataStream::write(bool value) {
        char type = DataType::BOOL;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(char value) {
        char type = DataType::CHAR;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(int value) {
        char type = DataType::INT;
        //std::cout << "Hello from int" << std::endl;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(float value) {
        char type = DataType::FLOAT;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(double value) {
        char type = DataType::DOUBLE;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(size_t value) {
        char type = DataType::SIZE_T;
        write((char*)(&type), sizeof(type));
        write((char*)(&value), sizeof(value));
    }
    void DataStream::write(const char* value) {
        char type = DataType::STRING;
        write((char*)(&type), sizeof(type));
        int len = std::strlen(value);
        write((char*)(&len), sizeof(len));
        write(value, len);
    }
    void DataStream::write(const std::string& value) {
        char type = DataType::STRING;
        write((char*)(&type), sizeof(type));
        auto len = value.size();

        //std::cout << len << std::endl;
        write(len);
        write(value.data(), len);
    }


    template<typename T, typename U>
    void DataStream::write(const std::pair<T, U>& value) {
        char type = DataType::PAIR;
        write((char*)(&type), sizeof(type));
        int len = static_cast<int>(value.size());
        write(len);
        write(value.first);
        write(value.second);
    }
    template<typename T>
    void DataStream::write(const std::vector<T>& value) {
        char type = DataType::VECTOR;
        write((char*)(&type), sizeof(type));
        auto len = value.size();
        write(len);
        for (const auto& it : value) {
            write(it);
        }
    }
    template<typename T>
    void DataStream::write(const std::list<T>& value) {
        char type = DataType::LIST;
        write((char*)(&type), sizeof(type));
        int len = static_cast<int>(value.size());
        write(len);
        for (const auto& it : value) {
            write(it);
        }
    }
    template<typename T, typename U>
    void DataStream::write(const std::map<T, U>& value) {
        char type = DataType::MAP;
        write((char*)&type, sizeof(type));
        int len = static_cast<int>(value.size());
        write(len);
        for (const auto& it : value) {
            write(it.first);
            write(it.second);
        }
    }
    template<typename T>
    void DataStream::write(const std::set<T>& value) {
        char type = DataType::SET;
        write((char*)(&type), sizeof(type));
        int len = static_cast<int>(value.size());
        write(len);
        for (const auto& it : value) {
            write(it);
        }
    }

    bool DataStream::read(bool& value) {
        if (m_buf[m_pos] != DataType::BOOL) {
            return false;
        }
        ++m_pos;
        value = m_buf[m_pos++];
        return true;
    }
    bool DataStream::read(char& value) {
        if (m_buf[m_pos] != DataType::CHAR) {
            return false;
        }
        ++m_pos;
        value = m_buf[m_pos++];
        return true;
    }
    bool DataStream::read(int& value) {
        if (m_buf[m_pos] != DataType::INT)
            return false;
        ++m_pos;
        value = *(int*)(&m_buf[m_pos]);
        //std::cout << "Hello from read int:" << value;
        m_pos += sizeof(int);
        return true;
    }
    bool DataStream::read(double& value) {
        if (m_buf[m_pos] != DataType::DOUBLE)
            return false;
        ++m_pos;
        value = *(double*)&m_buf[m_pos];
        m_pos += sizeof(double);
        return true;
    }
    bool DataStream::read(float& value) {
        if (m_buf[m_pos] != DataType::FLOAT)
            return false;
        ++m_pos;
        value = *(float*)&m_buf[m_pos];
        m_pos += sizeof(float);
        return true;
    }
    bool DataStream::read(size_t& value) {
        if (m_buf[m_pos] != DataType::SIZE_T)
            return false;
        ++m_pos;
        value = *(size_t*)&m_buf[m_pos];
        m_pos += sizeof(size_t);
        return true;
    }
    bool DataStream::read(std::string& value) {
        if (m_buf[m_pos] != DataType::STRING) {
            return false;
        }
        ++m_pos;
        size_t len;
        read(len);
        if (len < 0) {
            return false;
        }
        value.assign(&(m_buf[m_pos]), len);
        m_pos += len;
        return true;

    }


    template<typename T, typename U>
    bool DataStream::read(std::pair<T, U>& value) {
        if (m_buf[m_pos] != DataType::PAIR) {
            return false;
        }
        ++m_pos;
        int len;
        read(len);
        T pair_first;
        U pair_second;
        read(pair_first);
        read(pair_second);
        value.first = pair_first;
        value.second = pair_second;
        return true;
    }
    template<typename T>
    bool DataStream::read(std::vector<T>& value) {
        if (m_buf[m_pos] != DataType::VECTOR) {
            return false;
        }
        ++m_pos;
        int len;
        read(len);
        T item;
        for (int i = 0; i < len; i++) {
            read(item);
            value.emplace_back(item);
        }
        return true;
    }
    template<typename T>
    bool DataStream::read(std::list<T>& value) {
        if (m_buf[m_pos] != DataType::LIST)
            return false;
        ++m_pos;
        int len;
        read(len);
        value.resize(len);
        for (auto& it : value) {
            read(it);
        }
        return true;
    }
    template<typename T, typename U>
    bool DataStream::read(std::map<T, U>& value) {
        if (m_buf[m_pos] != DataType::MAP) {
            return false;
        }
        ++m_pos;
        int len;
        read(len);
        T map_first;
        U map_second;
        for (int i = 0; i < len; i++) {
            read(map_first);
            read(map_second);
            value.emplace(std::make_pair(map_first, map_second));
        }
        return true;
    }
    template<typename T>
    bool DataStream::read(std::set<T>& value) {
        if (m_buf[m_pos] != DataType::SET) {
            return false;
        }
        ++m_pos;
        int len;
        read(len);
        T item;
        for (int i = 0; i < len; i++) {
            read(item);
            value.emplace(item);
        }
        return true;
    }

    template<typename T>
    DataStream& DataStream::operator>>(T& value) {
        if (read(value))
            read_flag = true;
        else
            read_flag = false;
        return *this;
    }
    template<typename T>
    DataStream& DataStream::operator<<(const T& value) {
        write(value);
        return *this;
    }

    template<typename T>
    void serialize(const T& value, const std::string filename) {
        std::ofstream ofs(filename);
        DataStream ds;
        ds << value;
        ofs.write(ds.get_buf().data(), ds.get_buf().size());
        ofs.close();
    }
    template<typename T>
    void deserialize(T& value, const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (ifs.is_open()) {
            ifs.seekg(0, std::ios::end);
            std::streamsize size = ifs.tellg();
            ifs.seekg(0, std::ios::beg);

            std::vector<char> buffer(static_cast<size_t>(size));
            if (ifs.read(buffer.data(), size)) {
                DataStream ds;
                ds.get_buf() = std::move(buffer);
                ds >> value;
            }
            else {
                std::cerr << "Error: Failed to read from file" << std::endl;
            }
            ifs.close();
        }
        else {
            std::cerr << "Error: Failed to open file" << std::endl;
        }
    }

    template<typename T>
    struct Serializer;

    template<typename T>
    void DataStream::write(const T& value) {
        Serializer<T>::apply(*this, value);
    }
    template<typename T>
    bool DataStream::read(T& value) {
        return Serializer<T>::extract(*this, value);
    }

}


