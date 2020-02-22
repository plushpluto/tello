#include "command_socket.hpp"
#include "video_socket.hpp"
#include "state_socket.hpp"
#include "utils.hpp"

int main(){
  boost::asio::io_service io_service;

  CommandSocket c_tello(io_service, "192.168.10.1", "8889", "8889", 3,5);
  c_tello.addCommandToQueue("command");
  c_tello.addCommandToQueue("streamon");
  // boost::thread run_thread(boost::bind(&CommandSocket::DoNotLand, boost::ref(c_tello)));
  // boost::thread run_thread(c_tello.DoNotLand());
  c_tello.addCommandToQueue("stop");  
  c_tello.addCommandToQueue("takeoff");
  c_tello.addCommandToQueue("land");
  c_tello.executeQueue();

  // usleep(3000000);
  // VideoSocket v_tello(io_service, "0.0.0.0", "11111", "11111");
  // c_tello.addCommandToFrontOfQueue("stop");
  c_tello.stopQueueExecution();
  // usleep(2000000);/
  LogInfo() << "Restart";
  c_tello.executeQueue();

  StateSocket s_tello(io_service, "0.0.0.0", "8890", "8890");

  usleep(300000000); // Ensure this is greater than timeout to prevent seg faults
  io_service.stop();

  return 0;
}
