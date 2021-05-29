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
        System.out.println("Hi, I am " + getLocalName());
        
        // Display received messages
        addBehaviour(new CyclicBehaviour(this)
        {
            public void action()
            {
                // Processa mensagens recebidas
                ACLMessage msg = receive();
                if (msg != null)
                {
                    msgs_received++;
                    System.out.print("Message sent by :");
                    System.out.println(msg.getSender());
                    
                    display_message(msg);
                }
                block();
            }
        });
        
        // Display active agents
        addBehaviour(new TickerBehaviour(this, 5000)
        {
            protected void onTick()
            {
                System.out.println("");
                System.out.println(myAgent.getLocalName() + ":AgentManager");
                System.out.println("Active: ");
                agents = search_agents("");
                if (agents.length == 0)
                {
                    System.out.println("None.");
                } else
                {
                    for(int i=0;i<agents.length;i++)
                        System.out.println(agents[i].getLocalName());
                }

                System.out.println("");
                System.out.println("Sent:" + Integer.toString(msgs_sent) 
                        + "; Received:" + Integer.toString(msgs_received));
            }
        });
        
        // Agent polling
        addBehaviour(new TickerBehaviour(this, 2000)
        {
            protected void onTick()
            {
                if (agents != null)
                {
                    for (AID agente : agents)
                    {
                        ACLMessage msg = new ACLMessage(ACLMessage.QUERY_IF);
                        msg.setContent("send_proposal");
                        msg.addReceiver(agente);
                        send(msg);
                        msgs_sent++;
                    }
                }
                System.out.println("");
            }
        });
        
    }
    
    AID[] search_agents(String service) {
        DFAgentDescription dfd = new DFAgentDescription();
        ServiceDescription sd = new ServiceDescription();
        dfd.addServices(sd);

        SearchConstraints ALL = new SearchConstraints();
        ALL.setMaxResults(new Long(-1));

        try
        {
            DFAgentDescription[] result = DFService.search(this, dfd, ALL);
            AID[] agents_found = new AID[result.length];
            for (i = 0; i < result.length; i++)
            {
                agents_found[i] = result[i].getName();
            }
            return agents_found;

        } catch (FIPAException fe)
        {
            fe.printStackTrace();
        }

        return null;
    }
    
    void display_message(ACLMessage msg) {
        Properties properties = msg.getAllUserDefinedParameters();
        Enumeration parameters = properties.keys();
        String parameter;
        String value;
        //System.out.println(msg.toString());
        while (parameters.hasMoreElements())
        {
            parameter = (String) parameters.nextElement();
            value = (String) properties.getProperty(parameter);
            System.out.print(parameter);
            System.out.print(":");
            System.out.println(value);
        }       
    }
    
}
