#pragma once

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/base_class.hpp>


#include <sstream>
#include <memory>

enum class PacketType
{
    JoinResponse
};

struct Packet
{
public:
    virtual PacketType GetType() const = 0;

    unsigned packetID = 1;

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(packetID);
    }
};

struct JoinResponse : public Packet
{
public:
    virtual PacketType GetType() const { return PacketType::JoinResponse; }

    unsigned userID;

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::base_class<Packet>(this));
        ar(userID);
    }
};

CEREAL_REGISTER_TYPE(JoinResponse)


// Must be a smart pointer
template <typename T>
std::stringstream PacketToBinary(const T& packet)
{
    static_assert(
        std::is_base_of<std::unique_ptr<Packet>::element_type,
        T::element_type>::value, "T has to be derived from Packet");
    std::stringstream stream;
    {
        cereal::PortableBinaryOutputArchive out(stream);
        
        // NOTE: Cereal needs a pointer of base type
        // since it is too much of a hassle imo to convert all pointers to that type
        // I just convert it here. There may be some overhead by doing that
        std::unique_ptr<Packet> data(new T::element_type(*packet));
        out(data);
    }

    return stream;
}
std::unique_ptr<Packet> PacketFromBinary(std::stringstream& binary);
std::unique_ptr<Packet> PacketFromBinary(unsigned char* binary, unsigned count);