#pragma once
#include <cstdint>
#include <vector>

namespace ccsds
{
    // 定义帧头结构
    struct FrameHeader
    {
        uint8_t version : 3;          // 3位版本号
        uint8_t type : 1;             // 1位类型 (0=TM, 1=TC)
        uint8_t secondary_header : 1; // 1位二级头标志
        uint16_t data_length : 15;    // 15位数据长度（不包含帧头）
        uint16_t crc;                 // 16位CRC校验码
    };
    // TM 帧类
    class TMFrame
    {
    public:
        explicit TMFrame(const std::vector<uint8_t> &data);
        bool isValid() const;
        uint16_t getPacketLength() const;
        const std::vector<uint8_t> &getData() const;

    private:
        FrameHeader header_;
        std::vector<uint8_t> payload_;
        bool valid_;
    };

}