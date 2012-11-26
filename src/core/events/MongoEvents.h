#ifndef MONGOEVENTS_H
#define MONGOEVENTS_H

#include <QString>
#include <QStringList>
#include <QEvent>
#include "Core.h"

#define R_MESSAGE \
    public: \
        const static QEvent::Type EventType;


namespace Robomongo
{
    /**
     * @brief Error class
     */
    class Error
    {
    public:
        Error() :
            isNull(true) {}

        Error(const QString &errorMessage) :
            isNull(false),
            errorMessage(errorMessage) {}

        QString errorMessage;
        bool isNull;
    };


    /**
     * @brief Request & Response
     */

    class Request : public QEvent
    {
    public:
        Request(QEvent::Type type, QObject *sender) :
            QEvent(type),
            sender(sender) {}

        QObject *sender;
    };

    class Response : public QEvent
    {
    public:
        Response(QEvent::Type type) :
            QEvent(type) {}

        Response(QEvent::Type type, Error error) :
            QEvent(type),
            error(error) {}

        bool isError() const { return !error.isNull; }
        QString errorMessage() const { return error.errorMessage; }

        Error error;
    };


    /**
     * @brief EstablishConnection
     */

    class EstablishConnectionRequest : public Request
    {
        R_MESSAGE

        EstablishConnectionRequest(QObject *sender) :
            Request(EventType, sender) {}
    };

    class EstablishConnectionResponse : public Response
    {
        R_MESSAGE

        EstablishConnectionResponse(const QString &address) :
            Response(EventType),
            address(address) {}

        EstablishConnectionResponse(const Error &error) :
            Response(EventType, error) {}

        QString address;
    };


    /**
     * @brief LoadDatabaseNames
     */

    class LoadDatabaseNamesRequest : public Request
    {
        R_MESSAGE

        LoadDatabaseNamesRequest(QObject *sender) :
            Request(EventType, sender) {}
    };

    class LoadDatabaseNamesResponse : public Response
    {
        R_MESSAGE

        LoadDatabaseNamesResponse(const QStringList &databaseNames) :
            Response(EventType),
            databaseNames(databaseNames) {}

        LoadDatabaseNamesResponse(const Error &error) :
            Response(EventType, error) {}

        QStringList databaseNames;
    };


    /**
     * @brief LoadCollectionNames
     */

    class LoadCollectionNamesRequest : public Request
    {
        R_MESSAGE

        LoadCollectionNamesRequest(QObject *sender, const QString &databaseName) :
            Request(EventType, sender),
            databaseName(databaseName) {}

        QString databaseName;
    };

    class LoadCollectionNamesResponse : public Response
    {
        R_MESSAGE

        LoadCollectionNamesResponse(const QString &databaseName, const QStringList &collectionNames) :
            Response(EventType),
            databaseName(databaseName),
            collectionNames(collectionNames) { }

        LoadCollectionNamesResponse(const Error &error) :
            Response(EventType, error) {}

        QString databaseName;
        QStringList collectionNames;
    };

    class SomethingHappened : public QEvent
    {
        R_MESSAGE

        SomethingHappened(const QString &something) :
            QEvent(EventType),
            something(something) { }

        QString something;
    };

    class ConnectingEvent : public QEvent
    {
        R_MESSAGE

        ConnectingEvent(const MongoServerPtr &server) :
            QEvent(EventType),
            server(server) { }

        MongoServerPtr server;
    };

    class OpeningShellEvent : public QEvent
    {
        R_MESSAGE

        OpeningShellEvent(const MongoShellPtr &shell) :
            QEvent(EventType),
            shell(shell) { }

        MongoShellPtr shell;
    };

    class ConnectionFailedEvent : public QEvent
    {
        R_MESSAGE

        ConnectionFailedEvent(const MongoServerPtr &server) :
            QEvent(EventType),
            server(server) { }

        MongoServerPtr server;
    };

    class ConnectionEstablishedEvent : public QEvent
    {
        R_MESSAGE

        ConnectionEstablishedEvent(const MongoServerPtr &server) :
            QEvent(EventType),
            server(server) { }

        MongoServerPtr server;
    };

    class DatabaseListLoadedEvent : public QEvent
    {
        R_MESSAGE

        DatabaseListLoadedEvent(const QList<MongoDatabasePtr> &list) :
            QEvent(EventType),
            list(list) { }

        QList<MongoDatabasePtr> list;
    };

    class CollectionListLoadedEvent : public QEvent
    {
        R_MESSAGE

        CollectionListLoadedEvent(const QList<MongoCollectionPtr> &list) :
            QEvent(EventType),
            list(list) { }

        QList<MongoCollectionPtr> list;
    };

}

#endif // MONGOEVENTS_H