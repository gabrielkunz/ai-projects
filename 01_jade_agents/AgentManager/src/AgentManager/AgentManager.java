package AgentManager;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.*;
import jade.domain.DFService;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.SearchConstraints;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.domain.FIPAException;
import jade.lang.acl.ACLMessage;
import static jade.tools.sniffer.Agent.i;
import jade.util.leap.Properties;
import java.util.Enumeration;

public class AgentManager extends Agent {
    AID agents[];
    int msgs_sent = 0;
    int msgs_received = 0;
    
    @Override
    protected void setup() {
        
    }
    
    AID[] search_agents(String service) {
        return null;
    }
    
    void display_message(ACLMessage msg) {
        
    }
    
}
