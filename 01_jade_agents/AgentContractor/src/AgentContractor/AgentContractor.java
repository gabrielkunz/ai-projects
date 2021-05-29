package AgentContractor;

import jade.core.Agent;
import jade.core.behaviours.*;
import jade.domain.DFService;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.domain.FIPAException;
import jade.lang.acl.ACLMessage;

public class AgentContractor extends Agent {
    @Override
    protected void setup() {
        System.out.println("Hi, I am " + getLocalName());

        ServiceDescription sd = new ServiceDescription();
        sd.setType("painting");
        sd.setName("PaintShop1");
        sd.setOwnership(getLocalName());
        register(sd);

        addBehaviour(new CyclicBehaviour(this)
        {
            public void action()
            {
                ACLMessage msg = receive();
                if (msg != null)
                {
                    ACLMessage reply = msg.createReply();
                    if (msg.getContent().equals("send_proposal"))
                    {
                        reply.setPerformative(ACLMessage.INFORM);
                        reply.setContent("Sending proposal:");
                        send(reply);
                    }
                }
                block();
            }
        });
    }
    
    protected void take_down() {
        try {
            DFService.deregister(this);
        } catch (FIPAException e) {
        }
        doDelete();
    }
    
    void register(ServiceDescription sd) {
        DFAgentDescription dfd = new DFAgentDescription();
        dfd.setName(getAID());
        dfd.addServices(sd);

        try {
            DFService.register(this, dfd);
        } catch (FIPAException fe) {
        }
    }
    
}
