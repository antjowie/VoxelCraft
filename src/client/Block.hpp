#pragma once

enum BlockType
{
    Grass,
    Stone,

    Count
};

struct BlockMeta
{
    BlockType type;
    Texture<unsigned> texture;
};

class BlockMetaFactory
{
public:

    void AddBlockMeta(const BlockMeta &block)
    {
        assert(m_blocks.count(block.type) == 0);
        m_blocks[block.type] = block;
    }

    const BlockMeta& GetBlockMeta(BlockType type) const
    {
        return m_blocks.at(type);
    }

    BlockMeta CreateBlockMeta(BlockType type) const
    {
        return m_blocks.at(type);
    }

    const std::unordered_map<BlockType, BlockMeta>& GetData() const
    {
        return m_blocks;
    }

private:
    std::unordered_map<BlockType, BlockMeta> m_blocks;
};