#include "Net/Packet.h"

std::stringstream PacketToBinary(Packet& packet)
{
    std::stringstream stream;
    {
        cereal::PortableBinaryOutputArchive out(stream);
        out << packet;
    }

    return stream;
}

std::unique_ptr<Packet> PacketFromBinary(unsigned char* binary, unsigned count)
{
    // TODO: Find a way to make a stream use an existing buffer
    // instead of copying it
    std::stringstream stream;
    for (size_t i = 0; i < count; i++)
    {
        stream << binary[i];
    }

    return std::move(PacketFromBinary(stream));
}

std::unique_ptr<Packet> PacketFromBinary(std::stringstream& binary)
{
    std::unique_ptr<Packet> packet;

    {
        cereal::PortableBinaryInputArchive in(binary);
        in >> packet;
    }

    return std::move(packet);
}