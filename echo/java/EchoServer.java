/*  Copyright (2016) by Alexander Diemand
 *  MIT license; see file "LICENSE"
 */

// the original code has been copied from echo server example
import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;

public class EchoServer {

    public static void main(String[] args) throws Exception {

        // we listen on this port, localhost
        int port = 24937;
        ServerSocket srsock = new ServerSocket(port);
        System.err.println("Echo server on " + port + "@localhost");

        while (true) {

            Socket clsock = srsock.accept();
            //System.err.println("accept()");

            //In  in  = new In (clsock);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clsock.getInputStream()));
            //Out out = new Out(clsock);
            PrintWriter out = new PrintWriter(clsock.getOutputStream());

            // read all data - echo to client
            String s;
            while ((s = in.readLine()) != null) {
                //System.err.println("   read " + s);
                // interpret input
                try {
                    double d = Double.parseDouble(s);
                    s = String.valueOf(d*2.0+1.0);
                } catch (Exception e) {
                    e.printStackTrace();
                    s = "error";
                }
                
                // print out
                //out.println(s);
                out.print(s);
                out.flush();
                //break;
            }

            // done
            out.close();
            in.close();
            clsock.close();
            //System.err.println("close()");
        }
    }
}


