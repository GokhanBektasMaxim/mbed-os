/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MBED_GAP_ADVERTISING_DATA_H__
#define MBED_GAP_ADVERTISING_DATA_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "platform/Span.h"
#include "platform/NonCopyable.h"

#include "ble/blecommon.h"
#include "ble/SafeEnum.h"
#include "UUID.h"
#include "ble/gap/Types.h"

namespace ble {

/**
 * @addtogroup ble
 * @{
 * @addtogroup gap
 * @{
 */

/*!
 * List of standard Advertising Data types.
 *
 * These AD types are used to describe the capabilities of the peripheral
 * and are inserted inside the advertising or scan response payloads.
 *
 * @par Source
 *
 * @li @c Bluetooth Core Specification 4.0 (Vol. 3), Part C, Section 11, 18.
 * @li @c https://www.bluetooth.org/en-us/specification/assigned-numbers/generic-access-profile.
 */
struct adv_data_type_t : SafeEnum<adv_data_type_t, uint8_t> {
    /** struct scoped enum wrapped by the class */
    enum type {
        /**
         * Flags, refer to AdvertisingData::Flags_t.
         */
        FLAGS = 0x01,

        /**
         * Incomplete list of 16-bit Service IDs.
         */
        INCOMPLETE_LIST_16BIT_SERVICE_IDS = 0x02,

        /**
         * Complete list of 16-bit Service IDs.
         */
        COMPLETE_LIST_16BIT_SERVICE_IDS = 0x03,

        /**
         * Incomplete list of 32-bit Service IDs (not relevant for Bluetooth 4.0).
         */
        INCOMPLETE_LIST_32BIT_SERVICE_IDS = 0x04,

        /**
         * Complete list of 32-bit Service IDs (not relevant for Bluetooth 4.0).
         */
        COMPLETE_LIST_32BIT_SERVICE_IDS = 0x05,

        /**
         * Incomplete list of 128-bit Service IDs.
         */
        INCOMPLETE_LIST_128BIT_SERVICE_IDS = 0x06,

        /**
         * Complete list of 128-bit Service IDs.
         */
        COMPLETE_LIST_128BIT_SERVICE_IDS = 0x07,

        /**
         * Shortened Local Name.
         */
        SHORTENED_LOCAL_NAME = 0x08,

        /**
         * Complete Local Name.
         */
        COMPLETE_LOCAL_NAME = 0x09,

        /**
         * TX Power Level (in dBm).
         */
        TX_POWER_LEVEL = 0x0A,

        /**
         * Device ID.
         */
        DEVICE_ID = 0x10,

        /**
         * Slave Connection Interval Range.
         */
        SLAVE_CONNECTION_INTERVAL_RANGE = 0x12,

        /**
         * List of 128-bit service UUIDs the device is looking for.
         */
        LIST_16BIT_SOLICITATION_IDS = 0x14,

        /**
         * List of 128-bit service UUIDs the device is looking for.
         */
        LIST_128BIT_SOLICITATION_IDS = 0x15,

        /**
         * Service Data.
         */
        SERVICE_DATA = 0x16,

        /**
         * Service Data.
         */
        SERVICE_DATA_16BIT_ID = 0x16,

        /**
         * Service Data.
         */
        SERVICE_DATA_128BIT_ID = 0x21,

        /**
         * Appearance, refer to AdvertisingData::Appearance_t.
         */
        APPEARANCE = 0x19,

        /**
         * Advertising Interval.
         */
        ADVERTISING_INTERVAL = 0x1A,

        /**
         * Manufacturer Specific Data.
         */
        MANUFACTURER_SPECIFIC_DATA = 0xFF
    };

    /**
     * Construct a new instance of adv_data_type_t.
     */
    adv_data_type_t(type value) : SafeEnum(value)
    {
    }
};


/**
 *  Set of advertising flags.
 *
 *  @note LE_LIMITED_DISCOVERABLE and LE_GENERAL_DISCOVERABLE are mutually
 *  exclusive
 *
 *  @li @c Bluetooth Core Specification 4.0 (Vol. 3), Part C, Section 18.1.
 */
struct adv_data_flags_t {
    enum {
        LE_LIMITED_DISCOVERABLE = 0x01, /**< Discoverable for a limited period of time.*/
        LE_GENERAL_DISCOVERABLE = 0x02, /**< Discoverable at any moment. */
        BREDR_NOT_SUPPORTED = 0x04, /**< LE only and does not support Bluetooth Enhanced DataRate. */
        SIMULTANEOUS_LE_BREDR_C = 0x08, /**< Not relevant - dual mode only. */
        SIMULTANEOUS_LE_BREDR_H = 0x10  /**< Not relevant - dual mode only. */
    };

    static const uint8_t default_flags = BREDR_NOT_SUPPORTED | LE_GENERAL_DISCOVERABLE;

    /** Create from raw value */
    adv_data_flags_t(uint8_t value = 0) : _value(value)
    {
    }

    adv_data_flags_t &setGeneralDiscoverable(bool enable = true)
    {
        _value &= ~0x03;
        if (enable) {
            _value |= LE_GENERAL_DISCOVERABLE;
        }
        return *this;
    }

    adv_data_flags_t &setLimitedDiscoverable(bool enable = true)
    {
        _value &= ~0x03;
        if (enable) {
            _value |= LE_LIMITED_DISCOVERABLE;
        }
        return *this;
    }

    adv_data_flags_t &setBredrNotSupported(bool enable = true)
    {
        _value &= ~BREDR_NOT_SUPPORTED;
        if (enable) {
            _value |= BREDR_NOT_SUPPORTED;
        }
        return *this;
    }

    adv_data_flags_t &setSimultaneousLeBredrC(bool enable = true)
    {
        _value &= ~SIMULTANEOUS_LE_BREDR_C;
        if (enable) {
            _value |= SIMULTANEOUS_LE_BREDR_C;
        }
        return *this;
    }

    adv_data_flags_t &setSimultaneousLeBredrH(bool enable = true)
    {
        _value &= ~SIMULTANEOUS_LE_BREDR_H;
        if (enable) {
            _value |= SIMULTANEOUS_LE_BREDR_H;
        }
        return *this;
    }

    bool getGeneralDiscoverable()
    {
        return _value & LE_GENERAL_DISCOVERABLE;
    }

    bool getlimitedDiscoverable()
    {
        return _value & LE_LIMITED_DISCOVERABLE;
    }

    bool getBrEdrNotSupported()
    {
        return _value & BREDR_NOT_SUPPORTED;
    }

    bool getSimultaneousLeBredrC()
    {
        return _value & SIMULTANEOUS_LE_BREDR_C;
    }

    bool getSimultaneousLeBredrH()
    {
        return _value & SIMULTANEOUS_LE_BREDR_H;
    }

    void clear()
    {
        _value = 0;
    }

    uint8_t value()
    {
        return _value;
    }

private:
    uint8_t _value;
};


/**
 *  Enumeration of values for the adv_data_type_t::APPEARANCE.
 *
 *  These values describe the physical shape or appearance of the device.
 *
 *  @par Source
 *
 *  @li @c Bluetooth Core Specification Supplement, Part A, Section 1.12.
 *  @li @c Bluetooth Core Specification 4.0 (Vol. 3), Part C, Section 12.2.
 *  @li @c https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.gap.appearance.xml.
 */
struct adv_data_appearance_t : SafeEnum<adv_data_appearance_t, uint16_t> {
    /** struct scoped enum wrapped by the class */
    enum type {
        /**
         * Unknown or unspecified appearance type.
         */
        UNKNOWN = 0,

        /**
         * Generic Phone.
         */
        GENERIC_PHONE = 64,

        /**
         * Generic Computer.
         */
        GENERIC_COMPUTER = 128,

        /**
         * Generic Watch.
         */
        GENERIC_WATCH = 192,

        /**
         * Sports Watch.
         */
        WATCH_SPORTS_WATCH = 193,

        /**
         * Generic Clock.
         */
        GENERIC_CLOCK = 256,

        /**
         * Generic Display.
         */
        GENERIC_DISPLAY = 320,

        /**
         * Generic Remote Control.
         */
        GENERIC_REMOTE_CONTROL = 384,

        /**
         * Generic Eye Glasses.
         */
        GENERIC_EYE_GLASSES = 448,

        /**
         * Generic Tag.
         */
        GENERIC_TAG = 512,

        /**
         * Generic Keyring.
         */
        GENERIC_KEYRING = 576,

        /**
         * Generic Media Player.
         */
        GENERIC_MEDIA_PLAYER = 640,

        /**
         * Generic Bar Code Scanner.
         */
        GENERIC_BARCODE_SCANNER = 704,

        /**
         * Generic Thermometer.
         */
        GENERIC_THERMOMETER = 768,

        /**
         * Ear Thermometer.
         */
        THERMOMETER_EAR = 769,

        /**
         * Generic Heart Rate Sensor.
         */
        GENERIC_HEART_RATE_SENSOR = 832,

        /**
         * Belt Heart Rate Sensor.
         */
        HEART_RATE_SENSOR_HEART_RATE_BELT = 833,

        /**
         * Generic Blood Pressure.
         */
        GENERIC_BLOOD_PRESSURE = 896,

        /**
         * Arm Blood Pressure.
         */
        BLOOD_PRESSURE_ARM = 897,

        /**
         * Wrist Blood Pressure.
         */
        BLOOD_PRESSURE_WRIST = 898,

        /**
         * Human Interface Device (HID).
         */
        HUMAN_INTERFACE_DEVICE_HID = 960,

        /**
         * Keyboard.
         */
        KEYBOARD = 961,

        /**
         * Mouse.
         */
        MOUSE = 962,

        /**
         * Joystick.
         */
        JOYSTICK = 963,

        /**
         * Gamepad.
         */
        GAMEPAD = 964,

        /**
         * Digitizer Tablet.
         */
        DIGITIZER_TABLET = 965,

        /**
         * Card Reader.
         */
        CARD_READER = 966,

        /**
         * Digital Pen.
         */
        DIGITAL_PEN = 967,

        /**
         * Bar Code Scanner.
         */
        BARCODE_SCANNER = 968,

        /**
         * Generic Glucose Meter.
         */
        GENERIC_GLUCOSE_METER = 1024,

        /**
         * Generic Running/Walking Sensor.
         */
        GENERIC_RUNNING_WALKING_SENSOR = 1088,

        /**
         * In Shoe Running/Walking Sensor.
         */
        RUNNING_WALKING_SENSOR_IN_SHOE = 1089,

        /**
         * On Shoe Running/Walking Sensor.
         */
        RUNNING_WALKING_SENSOR_ON_SHOE = 1090,

        /**
         * On Hip Running/Walking Sensor.
         */
        RUNNING_WALKING_SENSOR_ON_HIP = 1091,

        /**
         * Generic Cycling.
         */
        GENERIC_CYCLING = 1152,

        /**
         * Cycling Computer.
         */
        CYCLING_CYCLING_COMPUTER = 1153,

        /**
         * Cycling Speed Sensor.
         */
        CYCLING_SPEED_SENSOR = 1154,

        /**
         * Cycling Cadence Sensor.
         */
        CYCLING_CADENCE_SENSOR = 1155,

        /**
         * Cycling Power Sensor.
         */
        CYCLING_POWER_SENSOR = 1156,

        /**
         * Cycling Speed and Cadence Sensor.
         */
        CYCLING_SPEED_AND_CADENCE_SENSOR = 1157,

        /**
         * Generic Pulse Oximeter.
         */
        PULSE_OXIMETER_GENERIC = 3136,

        /**
         * Fingertip Pulse Oximeter.
         */
        PULSE_OXIMETER_FINGERTIP = 3137,

        /**
         * Wrist Worn Pulse Oximeter.
         */
        PULSE_OXIMETER_WRIST_WORN = 3138,

        /**
         * Generic Weight Scale.
         */
        GENERIC_WEIGHT_SCALE = 3200,

        /**
         * Generic Outdoor.
         */
        OUTDOOR_GENERIC = 5184,

        /**
         * Outdoor Location Display Device.
         */
        OUTDOOR_LOCATION_DISPLAY_DEVICE = 5185,

        /**
         * Outdoor Location and Navigation Display Device.
         */
        OUTDOOR_LOCATION_AND_NAVIGATION_DISPLAY_DEVICE = 5186,

        /**
         * Outdoor Location Pod.
         */
        OUTDOOR_LOCATION_POD = 5187,

        /**
         * Outdoor Location and Navigation Pod.
         */
        OUTDOOR_LOCATION_AND_NAVIGATION_POD = 5188
    };

    /**
     * Construct a new instance of adv_data_appearance_t.
     */
    adv_data_appearance_t(type value) : SafeEnum(value)
    {
    }
};

/**
 * Build advertising data.
 *
 * The builder accept an array of bytes in input and returns the result of the
 * construction with getAdvertisingData().
 */
class AdvertisingDataBuilder {
public:
    /** Advertising data needs a user provided buffer to store the data.
     *
     * @param buffer Buffer used to store the data.
     * @note Use Gap::getMaxAdvertisingDataLength() to find out how much can be accepted.
     */
    AdvertisingDataBuilder(mbed::Span<uint8_t> buffer);

    /** Advertising data needs a user provided buffer to store the data.
     *
     * @param buffer Pointer to buffer to be used for storing advertising data.
     * @param buffer_size Size of the buffer.
     * @note Use Gap::getMaxAdvertisingDataLength() to find out how much can be accepted.
     */
    AdvertisingDataBuilder(uint8_t *buffer, size_t buffer_size);

    /**
     * Get the subspan of the buffer containing valid data.
     *
     * @return A Span containing the payload.
     */
    mbed::Span<const uint8_t> getAdvertisingData() const;

    /**
     * Add a new field into the payload. Will return an error if type is already present.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType The type of the field to add.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_OPERATION_NOT_PERMITTED if data type already present.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t addData(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Replace a new field into the payload. Will fail if type is not already present.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType The type of the field to add.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_NOT_FOUND if data type not present.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t replaceData(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Append data to an existing field in the payload. Will fail if type is not already
     * present.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType The type of the field to add.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_NOT_FOUND if data type not present.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t appendData(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Remove existing date of given type. Will return an error if type is not present.
     *
     * @param[in] advDataType The type of the field to remove.
     *
     * @return BLE_ERROR_NONE returned on success, BLE_ERROR_INVALID_PARAM if field doesn't exist
     */
    ble_error_t removeData(adv_data_type_t advDataType);

    /**
     * Adds a new field into the payload. If the supplied advertising data type is
     * already present in the advertising payload, then the value is replaced.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType The type of the field to add.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t addOrReplaceData(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Adds a new field into the payload. If the supplied advertising data type is
     * already present in the advertising payload, then the value is replaced.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType The type of the field to add.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t addOrAppendData(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Clears the advertising data payload.
     *
     * @post getPayloadLen() returns 0.
     */
    void clear();

    /**
     * Add device appearance in the advertising payload.
     *
     * @param[in] appearance The appearance to advertise.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     *
     * @note This call is equivalent to calling addOrReplaceData() with
     * adv_data_type_t::APPEARANCE as the field type.
     */
    ble_error_t setAppearance(adv_data_appearance_t appearance);

    /**
     * Add BLE flags in the advertising payload.
     *
     * @param[in] flags Bitfield describing the capability of the device. See
     * allowed flags in Flags_t.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     *
     * @note This call is equivalent to calling addOrReplaceData() with
     * adv_data_type_t::FLAGS as the field type.
     */
    ble_error_t setFlags(
        adv_data_flags_t flags = adv_data_flags_t::default_flags
    );

    /**
     * Add the advertising TX in the advertising payload.
     *
     * @param[in] txPower Transmission power level in dB.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     *
     * @note This call is equivalent to calling addOrReplaceData() with
     * adv_data_type_t::TX_POWER_LEVEL as the field type.
     */
    ble_error_t setTxPowerAdvertised(advertising_power_t txPower);

    /**
     * Add device name to the advertising payload.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] name Null terminated string containing the name.
     * @param[in] complete Complete local name if true, otherwise
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t setName(const char *name, bool complete = true);

    /**
     * Add manufacturer specific data to the advertising payload.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] data New data to be added.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual
     *                                 data field or the data is too small (must contain
     *                                 2 bytes of manufacturer ID)
     */
    ble_error_t setManufacturerSpecificData(mbed::Span<const uint8_t> data);

    /**
     * Add advertising interval to the payload. This field can only carry 2 bytes.
     *
     * @param interval Interval to advertise. Cannot be larger than 0xFFFF.

     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if interval value outside of valid range.
     */
    ble_error_t setAdvertisingInterval(adv_interval_t interval);

    /**
     * Add connection interval preferences to the payload
     *
     * @param min Minimum connection interval to advertise.
     * @param max Maximum connection interval to advertise.

     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     */
    ble_error_t setConnectionIntervalPreference(
        conn_interval_t min,
        conn_interval_t max
    );

    /**
     * Add service data data to the advertising payload.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] service UUID of the service.
     * @param[in] data New data to be added.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if size of data is too big too fit in an individual data field.
     */
    ble_error_t setServiceData(UUID service, mbed::Span<const uint8_t> data);

    /**
     * Add local service IDs to the advertising payload. If they data can't fit
     * no modification will take place.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] data New data to be added.
     * @param[in] complete True if this is a complete list.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if number of UUIDs of any one type is too high.
     */
    ble_error_t setLocalServiceList(
        mbed::Span<const UUID> data,
        bool complete = true
    );

    /**
     * Add a list of UUIDs of solicited services.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] data List of 128 or 16 bit service UUIDs.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if number of UUIDs of any one type is too high.
     */
    ble_error_t setRequestedServiceList(mbed::Span<const UUID> data);

    /**
     * Return a span of data containing the the type of data requested.
     *
     * @param[out] data Span used to return the requested data.
     * @param[in] advDataType Data type to return.
     *
     * @return BLE_ERROR_NONE if data was found and BLE_ERROR_NOT_FOUND if not.
     */
    ble_error_t getData(
        mbed::Span<const uint8_t> &data,
        adv_data_type_t advDataType
    );

private:
    /**
    * Search advertisement data for a specific field.
    *
    * @param[in] type The type of the field to find.
    *
    * @return A pointer to the first element in the field if found. The first
    * element being the length of the field followed by the value of the field.
    * NULL if the field is not present in the payload.
    */
    uint8_t *findField(adv_data_type_t type);

    /**
     * Get field size (includes type and size bytes)
     *
     * @param type The field type.
     *
     * @return Size of the whole field including type and size bytes.
     */
    uint8_t getFieldSize(adv_data_type_t type);

    /**
     * Append advertising data based on the specified type.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType Type of the new data.
     * @param[in] fieldData Span of data to add.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     */
    ble_error_t addField(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData
    );

    /**
     * Append data to a field in the advertising payload.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] fieldData Span of data to add.
     * @param[in] field Pointer to the field in the advertising buffer.
     *
     * @return BLE_ERROR_NONE on success.
     */
    ble_error_t appendToField(
        mbed::Span<const uint8_t> fieldData,
        uint8_t *field
    );

    /**
     * Update in place the value of a field in the advertising payload.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] advDataType Type of the new data.
     * @param[in] fieldData Span of data to add.
     * @param[in] field Pointer to the field of type @p advDataType in the
     * advertising buffer.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     */
    ble_error_t replaceField(
        adv_data_type_t advDataType,
        mbed::Span<const uint8_t> fieldData,
        uint8_t *field
    );

    /**
     * Remove the field.
     *
     * @param[in] field Pointer to the field in the advertising buffer.
     *
     * @return BLE_ERROR_NONE on success.
     */
    ble_error_t removeField(uint8_t *field);

    /**
     * Add a list of UUIDs to given types.
     *
     * @note Data size for individual types cannot exceed 255 bytes.
     *
     * @param[in] data List of 128 or 16 bit service UUIDs.
     * @param[in] shortType Type of field to add the short UUIDs to.
     * @param[in] longType Type of field to add the long UUIDs to.
     *
     * @retval BLE_ERROR_NONE on success.
     * @retval BLE_ERROR_BUFFER_OVERFLOW if buffer is too small to contain the new data.
     * @retval BLE_ERROR_INVALID_PARAM if number of UUIDs of any one type is too high.
     */
    ble_error_t setUUIDData(
        mbed::Span<const UUID> data,
        adv_data_type_t shortType,
        adv_data_type_t longType
    );

private:
    /** The memory backing the the data provided by the user. */
    mbed::Span<uint8_t> _buffer;

    /** Length of the data added to the advertising buffer. */
    uint8_t _payload_length;
};

/**
 * @}
 * @}
 */

} // namespace ble

#endif /* ifndef MBED_GAP_ADVERTISING_DATA_H__ */
