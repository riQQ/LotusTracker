#include "../src/mtg/mtgalogparser.h"
#include "macros_test.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>

#include <QSignalSpy>
#include <QtTest/QtTest>

Q_DECLARE_METATYPE(Deck)
Q_DECLARE_METATYPE(PlayerInventory)

class TestMtgaLogParser: public QObject
{
    Q_OBJECT
private:
    MtgCards *mtgCards;
    MtgaLogParser *mtgaLogParser;

public:
    TestMtgaLogParser()
    {
        mtgCards = new MtgCards(this);
        mtgaLogParser = new MtgaLogParser(this, mtgCards);
    }

private slots:
    void testParsePlayerInventory()
    {
        qRegisterMetaType<PlayerInventory>();
        QString log;
        READ_LOG("PlayerInventory.txt", log);
        QSignalSpy spy(mtgaLogParser, &MtgaLogParser::sgnPlayerInventory);
        mtgaLogParser->parse(log);

        QCOMPARE(spy.count(), 1);
        QList<QVariant> args = spy.takeFirst();
        PlayerInventory playerInventory = args.first().value<PlayerInventory>();
        QVERIFY(playerInventory.wcMythic == 6);
    }

    void testParsePlayerInventoryUpdate()
    {
        QString log;
        READ_LOG("PlayerInventoryUpdate.txt", log);
        QSignalSpy spy(mtgaLogParser, &MtgaLogParser::sgnPlayerInventoryUpdate);
        mtgaLogParser->parse(log);

        QCOMPARE(spy.count(), 1);
        QList<QVariant> args = spy.takeFirst();
        QList<int> newCards = args.first().value<QList<int>>();
        QVERIFY(newCards.first() == 65963);
    }

    void testParsePlayerCollection()
    {
        qRegisterMetaType<QMap<int, int>>();
        QString log;
        READ_LOG("PlayerCollection.txt", log);
        QSignalSpy spy(mtgaLogParser, &MtgaLogParser::sgnPlayerCollection);
        mtgaLogParser->parse(log);

        QCOMPARE(spy.count(), 1);
        QList<QVariant> args = spy.takeFirst();
        QMap<int, int> playerCollection = args.first().value<QMap<int, int>>();
        QVERIFY(playerCollection.size() == 421);
        QVERIFY(playerCollection[66041] == 3);
    }

    void testParsePlayerDecks()
    {
        qRegisterMetaType<QList<Deck>>();
        QString log;
        READ_LOG("PlayerDecks.txt", log);
        QSignalSpy spy(mtgaLogParser, &MtgaLogParser::sgnPlayerDecks);
        mtgaLogParser->parse(log);

        QCOMPARE(spy.count(), 1);
        QList<QVariant> args = spy.takeFirst();
        QList<Deck> playerDecks = args.first().value<QList<Deck>>();
        QVERIFY(playerDecks.size() == 3);
        Card* card = mtgCards->findCard(66223);
        QVERIFY(playerDecks.first().cards[card] == 3);
    }

};