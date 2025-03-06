#ifndef INC_COMMS_USBCDCSERIAL_HPP_
#define INC_COMMS_USBCDCSERIAL_HPP_

#include "usbd_cdc_if.h" // Include USB CDC interface
#include "utility/PrintLite.h"
#include "toolbox.h"
#include "generics/Queue.h"
#include "utility/IWrite.h"

class USBSerial : public PrintLite
{
public:
    /**
     * Initializes the USB CDC interface.
     * @param handle Handle to the USB CDC interface.
     */
    USBSerial(USBD_CDC_HandleTypeDef *handle)
    {
        this->handle = handle;
    }

    USBSerial(USBD_CDC_HandleTypeDef *handle, uint8_t *buffer, uint32_t length)
        : queue(buffer, length)
    {
        this->handle = handle;
    }

    /**
     * Writes bytes to the USB CDC port.
     * @param buffer Pointer to the memory to write from.
     * @param length Number of bytes to write.
     */
    size_t write(const uint8_t *buffer, uint32_t length)
    {
        while (CDC_Transmit_FS((uint8_t *)buffer, length) == USBD_BUSY)
            ;
        return length;
    }

    /**
     * Writes a single character to the USB CDC port.
     * @param c The character.
     */
    size_t write(uint8_t c)
    {
        return write(&c, 1);
    }

    /**
     * Reads data from the USB CDC buffer.
     * @param buffer Pointer to store received data.
     * @param length Number of bytes to read.
     */
    size_t read(uint8_t *buffer, uint32_t length)
    {
        // Implement buffer handling (CDC stores incoming data in a global buffer)
        
        return length;
    }

    /**
     * Returns the number of available bytes.
     */
    uint32_t available()
    {
        // Implement logic to check available data in the USB CDC buffer
        return 0; // Placeholder: implement later
    }

private:
    USBD_CDC_HandleTypeDef *handle;
    Queue<uint8_t> queue;
    uint8_t *buffer;
    uint32_t length;
};

#endif /* INC_COMMS_USBCDCSERIAL_HPP_ */
