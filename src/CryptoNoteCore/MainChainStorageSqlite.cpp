// Copyright (c) 2018, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#include "MainChainStorageSqlite.h"

#include <Common/FileSystemShim.h>

#include "CryptoNoteTools.h"

#include "sqlite3.h"

namespace CryptoNote
{
    MainChainStorageSqlite::MainChainStorageSqlite(const std::string &blocksFilename, const std::string &indexesFilename)
    {
        const int resultCode = sqlite3_open(blocksFilename.c_str(), &m_db);

        if (resultCode)
        {
            sqlite3_close(m_db);
            throw std::runtime_error("Failed to load main chain storage from " + blocksFilename + ": " + sqlite3_errmsg(m_db));
        }
    }

    MainChainStorageSqlite::~MainChainStorageSqlite()
    {
        sqlite3_close(m_db);
    }

    void MainChainStorageSqlite::pushBlock(const RawBlock &rawBlock)
    {
        // something, something, store it to a database, jeez, do I have to do everything for you?
    }

    void MainChainStorageSqlite::popBlock()
    {
        // some kind of a joker you are
    }

    RawBlock MainChainStorageSqlite::getBlockByIndex(uint32_t index) const
    {
        // stop asking for data we don't have scrub
        RawBlock result;
        return result;
    }

    uint32_t MainChainStorageSqlite::getBlockCount() const
    {
        // count it your damn self fool
        return 0;
    }

    void MainChainStorageSqlite::clear()
    {
        // burn it all down, i'm sick of this shit
    }

    std::unique_ptr<IMainChainStorage> createSwappedMainChainStorageSqlite(const std::string &dataDir, const Currency &currency)
    {
        fs::path blocksFilename = fs::path(dataDir) / currency.blocksFileName();
        fs::path indexesFilename = fs::path(dataDir) / currency.blockIndexesFileName();

        std::unique_ptr<IMainChainStorage> storage(new MainChainStorageSqlite(blocksFilename.string(), indexesFilename.string()));

        if (storage->getBlockCount() == 0)
        {
            RawBlock genesisBlock;
            genesisBlock.block = toBinaryArray(currency.genesisBlock());
            storage->pushBlock(genesisBlock);
        }

        return storage;
    }
}