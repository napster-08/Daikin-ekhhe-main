
#pragma once

#include <string>
#include <map>
#include <type_traits>

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/time/real_time_clock.h"

#include "daikin_ekhhe_const.h"

namespace esphome {
namespace daikin_ekkhe {

class DaikinEkhheComponent;  // Forward declaration


class DaikinEkhheNumber : public number::Number {
 public:
    void control(float value) override;
    void set_parent(DaikinEkhheComponent *parent) { this->parent_ = parent; }
    // Needed so we can set this from python and then reference it in the control function
    void set_internal_id(const std::string &id) { this->internal_id_ = id; }

  private:
    DaikinEkhheComponent *parent_;
    std::string internal_id_;
};

class DaikinEkhheSelect : public select::Select, public Component {
 public:
  void control(const std::string &value) override;
  void set_select_mappings(std::map<std::string, int> mappings) {
    this->select_mappings_ = std::move(mappings);
  }
  // this stores the number to read/write for each select option
  std::map<std::string, int> get_select_mappings() {
      return this->select_mappings_;
  }
  void set_parent(DaikinEkhheComponent *parent) { this->parent_ = parent; }
  void set_internal_id(const std::string &id) { this->internal_id_ = id; }

  private:
   std::map<std::string, int> select_mappings_; 
   DaikinEkhheComponent *parent_;
   std::string internal_id_;
};

class DaikinEkhheComponent : public Component, public uart::UARTDevice {
 public:

  DaikinEkhheComponent() = default;
  enum EkhheError {
    EKHHE_ERROR_NONE,
    EKHHE_ERROR_PACKET_SIZE, 
    EKHHE_ERROR_BUFFER_EMPTY,
    EKHHE_ERROR_CHECKSUM,
  };


  // ========== INTERNAL METHODS ==========
  void setup() override;
  void loop() override;
  void update();
  void dump_config() override;
  void on_shutdown();
  void set_update_interval(int interval_ms);

  // Methods to register sensors, binary sensors, and numbers
  void register_sensor(const std::string &sensor_name, esphome::sensor::Sensor *sensor);
  void register_binary_sensor(const std::string &sensor_name, esphome::binary_sensor::BinarySensor *binary_sensor);
  void register_number(const std::string &number_name, esphome::number::Number *number);
  void register_select(const std::string &select_name, select::Select *select);
  void register_timestamp_sensor(esphome::text_sensor::TextSensor *sensor);

  // Methods to update values dynamically (only for registered components)
  void set_sensor_value(const std::string &sensor_name, float value);
  void set_binary_sensor_value(const std::string &sensor_name, bool value);
  void set_number_value(const std::string &number_name, float value);
  void set_select_value(const std::string &select_name, int value);
  void update_timestamp(uint8_t hour, uint8_t minute);

  // Allow UART command sending for Number/Select control
  void send_uart_cc_command(uint8_t index, uint8_t value, uint8_t bit_position);


  enum EkkheDDPacket {
    DD_PACKET_START_IDX = 0,
    DD_PACKET_B_IDX     = 6,
    DD_PACKET_A_IDX     = 7,
    DD_PACKET_C_IDX     = 8,
    DD_PACKET_D_IDX     = 10,
    DD_PACKET_E_IDX     = 11,
    DD_PACKET_F_IDX     = 12,
    DD_PACKET_G_IDX     = 13,
    DD_PACKET_H_IDX     = 14,
    DD_PACKET_I_IDX     = 18,
    DD_PACKET_DIG_IDX   = 21,
    DD_PACKET_END       = 40,
    DD_PACKET_SIZE      = 41,
  };

  enum EkhheD2Packet {
    D2_PACKET_START_IDX = 0,
    D2_PACKET_MASK1_IDX = 1,
    D2_PACKET_MASK2_IDX = 2,
    D2_PACKET_MODE_IDX  = 3,
    D2_PACKET_P4_IDX    = 4,
    D2_PACKET_ECO_TTARGET_IDX       = 13,
    D2_PACKET_AUTO_TTARGET_IDX      = 14,
    D2_PACKET_BOOST_TTGARGET_IDX    = 15,
    D2_PACKET_ELECTRIC_TTARGET_IDX  = 16,
    D2_PACKET_P3_IDX    = 22,
    D2_PACKET_HOUR_IDX  = 56,
    D2_PACKET_MIN_IDX   = 57,
    D2_PACKET_END       = 70, 
    D2_PACKET_SIZE      = 71,
  };

  enum EkhheD4Packet {
    D4_PACKET_START_IDX = 0,
    D4_PACKET_END       = 50,
    D4_PACKET_SIZE      = 51,
  };

  enum EkhheC1Packet {
    C1_PACKET_START_IDX = 0,
    C1_PACKET_END       = 50,
    C1_PACKET_SIZE      = 51,
  };

  enum EkhheCCPacket {
    CC_PACKET_START_IDX = 0,
    CC_PACKET_MASK1_IDX = 1,
    CC_PACKET_MASK2_IDX = 2,
    CC_PACKET_MODE_IDX  = 3,
    CC_PACKET_P4_IDX    = 4,
    CC_PACKET_ECO_TTARGET_IDX       = 13,
    CC_PACKET_AUTO_TTARGET_IDX      = 14,
    CC_PACKET_BOOST_TTGARGET_IDX    = 15,
    CC_PACKET_ELECTRIC_TTARGET_IDX  = 16,
    CC_PACKET_P3_IDX    = 22, 
    CC_PACKET_HOUR_IDX  = 57,
    CC_PACKET_MIN_IDX   = 58,
    CC_PACKET_END       = 70, 
    CC_PACKET_SIZE      = 71,
  };

  // This is the TX/control packet
  enum EkhheCDPacket {
    CD_PACKET_START_IDX = 0,
    CD_PACKET_END       = 70,
    CD_PACKET_SIZE      = 71,
  };

 private:
  // variables for sensors etc.
  std::map<std::string, esphome::sensor::Sensor *> sensors_;
  std::map<std::string, esphome::binary_sensor::BinarySensor *> binary_sensors_;
  std::map<std::string, esphome::number::Number *> numbers_;
  std::map<std::string, DaikinEkhheSelect *> selects_;
  text_sensor::TextSensor *timestamp_sensor_ = nullptr;
  esphome::time::RealTimeClock *clock;

  // UART Processing
  uint8_t ekhhe_checksum(const std::vector<uint8_t>& data_bytes);
  void parse_dd_packet(std::vector<uint8_t> buffer);
  void parse_d2_packet(std::vector<uint8_t> buffer);
  void parse_d4_packet(std::vector<uint8_t> buffer);
  void parse_c1_packet(std::vector<uint8_t> buffer);
  void parse_cc_packet(std::vector<uint8_t> buffer);
  void start_uart_cycle();
  void process_packet_set();
  bool packet_set_complete();
  void store_latest_packet(uint8_t byte);

  std::vector<uint8_t> last_d2_packet_;
  std::vector<uint8_t> last_dd_packet_;
  std::vector<uint8_t> last_cc_packet_;  // Always store CC for sending commands
  std::vector<uint8_t> last_c1_packet_;
  std::vector<uint8_t> last_d4_packet_;
  std::map<uint8_t, std::vector<uint8_t>> latest_packets_;

  bool uart_active_ = false;
  bool processing_updates_ = false;
  bool uart_tx_active_ = false; // used for SW "flow control" to avoid RS485 bus contention
  unsigned long last_rx_time_ = 0;

  // Cycle management
  unsigned long last_process_time_ = 0;
  unsigned long update_interval_ = 10000;
};

using namespace daikin_ekhhe;
// uint8_t variables
static const std::map<std::string, uint8_t> U_NUMBER_PARAM_INDEX = {
  {P3_ANTL_SET_T,           DaikinEkhheComponent::CC_PACKET_P3_IDX},
  {P4_ANTL_DURATION,        DaikinEkhheComponent::CC_PACKET_P4_IDX},
  {ECO_T_TEMPERATURE,       DaikinEkhheComponent::CC_PACKET_ECO_TTARGET_IDX},
  {AUTO_T_TEMPERATURE,      DaikinEkhheComponent::CC_PACKET_AUTO_TTARGET_IDX},
  {BOOST_T_TEMPERATURE,     DaikinEkhheComponent::CC_PACKET_BOOST_TTGARGET_IDX},
  {ELECTRIC_T_TEMPERATURE,  DaikinEkhheComponent::CC_PACKET_ELECTRIC_TTARGET_IDX},
};

// int8_t variables
//static const std::map<std::string, uint8_t> I_NUMBER_PARAM_INDEX = {
//  {P8_DEFR_START_THRES,       DaikinEkhheComponent::CC_PACKET_P8_IDX}, // int8_t
//  {P25_UP_WAT_T_OFFSET,       DaikinEkhheComponent::CC_PACKET_P25_IDX},
//  {P26_LOW_WAT_T_OFFSET,      DaikinEkhheComponent::CC_PACKET_P26_IDX},
//  {P27_INLET_T_OFFSET,        DaikinEkhheComponent::CC_PACKET_P27_IDX},
//  {P28_DEFR_T_OFFSET,         DaikinEkhheComponent::CC_PACKET_P28_IDX},
//  {P35_EEV_SH_SETPOINT,       DaikinEkhheComponent::CC_PACKET_P35_IDX},
//  {P41_AKP1_THRES,            DaikinEkhheComponent::CC_PACKET_P41_IDX},
//  {P42_AKP2_THRES,            DaikinEkhheComponent::CC_PACKET_P42_IDX},
//  {P43_AKP3_THRES,            DaikinEkhheComponent::CC_PACKET_P43_IDX},
//  {P44_EEV_KP1_GAIN,          DaikinEkhheComponent::CC_PACKET_P44_IDX},
//  {P45_EEV_KP2_GAIN,          DaikinEkhheComponent::CC_PACKET_P45_IDX},
//  {P46_EEV_KP3_GAIN,          DaikinEkhheComponent::CC_PACKET_P46_IDX},
//  {P48_MIN_INLET_T_HP,        DaikinEkhheComponent::CC_PACKET_P48_IDX},
//};

static const std::map<std::string, uint8_t> SELECT_PARAM_INDEX = {
  {OPERATIONAL_MODE,     DaikinEkhheComponent::CC_PACKET_MODE_IDX},
};

static const std::map<std::string, std::pair<uint8_t, uint8_t>> SELECT_BITMASKS = {
  {POWER_STATUS,          {DaikinEkhheComponent::CC_PACKET_MASK1_IDX, 0}}, 
};

static const uint8_t BIT_POSITION_NO_BITMASK = 255;
static const uint8_t PARAM_INDEX_INVALID = 255;


}  // namespace daikin_ekkhe
}  // namespace esphome











