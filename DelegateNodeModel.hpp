#pragma once

#include <QtCore/QObject>

#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModel>

#include <memory>
#include <vector>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class SimpleNodeData : public NodeData
{
public:
    NodeDataType type() const override { return NodeDataType{"SimpleData", "Simple Data"}; }
    
    // Vector to store connections from/to other nodes for each connector
    std::vector<std::vector<std::shared_ptr<NodeData>>> leftConnections;  // For the left connector
    std::vector<std::vector<std::shared_ptr<NodeData>>> rightConnections; // For the two right connectors
    
    SimpleNodeData() {
        // Initialize with one left connector
        leftConnections.resize(1);
        
        // Initialize with two right connectors
        rightConnections.resize(2);
    }
};

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SimpleDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    QString caption() const override { return QString("Simple Data Model"); }

    QString name() const override { return QString("SimpleDataModel"); }

public:
    unsigned int nPorts(PortType const portType) const override 
    { 
        // One left (input) connector, two right (output) connectors
        return (portType == PortType::In) ? 1 : 2; 
    }

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override
    {
        return SimpleNodeData().type();
    }

    std::shared_ptr<NodeData> outData(PortIndex const port) override
    {
        return std::make_shared<SimpleNodeData>();
    }

    void setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex) override 
    {
        // Store the connection data
        if (portIndex == 0 && data) { // For the left connector
            auto nodeData = std::dynamic_pointer_cast<SimpleNodeData>(_nodeData);
            if (nodeData) {
                nodeData->leftConnections[0].push_back(data);
            }
        }
    }

    QWidget *embeddedWidget() override { return nullptr; }

private:
    std::shared_ptr<SimpleNodeData> _nodeData{std::make_shared<SimpleNodeData>()};
};
