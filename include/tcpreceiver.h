///
/// @file
/// @copyright Copyright (C) 2017, Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
///
/// @brief
///
#ifndef OSI_VISUALIZER_TCPRECEIVER_H
#define OSI_VISUALIZER_TCPRECEIVER_H

#include <zmq.hpp>
#include "types.h"
#include <QtConcurrent/QtConcurrent>

#include "imessagesource.h"
#include "osi_sensordata.pb.h"

class TCPReceiver : public QObject, public IMessageSource
{
    Q_OBJECT

  public:
    TCPReceiver(int type);

  signals:
    void Connected(DataType dataType);
    void Disconnected(const QString& message = "");
    void UpdateSliderTime(int sliderValue);
    void MessageSDReceived(const osi3::SensorData& sd);
    void MessageSVReceived(const osi3::SensorView& sv);

  public slots:
    void DisconnectRequested();
    void ConnectRequested(const QString& ipAddress, const QString& port, DataType dataType);

  private:
    void ReceiveLoop();

    bool isRunning_;
    bool isThreadTerminated_;

    int socketType_;
    std::string currentPort_;
    std::string currentEndpoint_;
    zmq::context_t context_;
    zmq::socket_t socket_;
    DataType currentDataType_;
};
#endif  // OSI_VISUALIZER_TCPRECEIVER_H