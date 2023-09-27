import React, { useEffect } from "react";
import { useRouter } from 'next/router';
import { Button, Form } from "antd";
import { InputOTP } from "antd-input-otp"; // Don't forget to import this too!
import { useState } from "react";
import axios from "axios";
import { clientConfig } from "../../oauth";

const server_uri = clientConfig.server_uri;

const containerStyle = {
  background: 'rgb(60, 119, 246)',
  fontFamily: 'work sans',
  fontSize: '100%',
  display: 'flex',
  justifyContent: 'center',
  alignItems: 'center',
  height: '100vh',
};

const loginFormStyle = {
  maxWidth: '800px',
  maxHeight: '120px',
  width: '40%',
  height: '60%',
  backgroundColor: '#ffffff',
  borderRadius: '25px',
  padding: '2rem',
};

const headerTitleStyle = {
  textAlign: 'center',
  fontFamily: 'open sans, sans-serif',
  margin: '0',
  fontSize: '2rem',
  paddingBottom: '2rem',
};

const contentStyle = {
  textAlign: 'center',
  fontFamily: 'open sans, sans-serif',
};

const buttonStyle = {
  borderRadius: '25px',
  width: '100%',
  height: '40px',
  fontSize: '1.3rem',
  color: 'white',
  fontWeight: '700',
  background: 'rgb(60, 119, 246)',
  border: '0px',
  cursor: 'pointer',
  transition: 'opacity 0.25s ease-out',
};

export default function LibraryIconPage() {
  axios.defaults.withCredentials = true;
  const router = useRouter();

  const [value, setValue] = useState([]); // Since the value will be array of string, the default value of state is empty array.

  // #region The Controlled Logic
  const [otpValues, setOtpValues] = useState([]);
  // #endregion

  // #region The Uncontrolled Logic
  const [form] = Form.useForm();

  const handleFinish = (values) => {
    // The value will be array of string
    // Check the field if there is no value, or value is undefined/empty string

    const { otp } = values;
    const otpNumber: string = otp?.join().replaceAll(",", "");
    console.log(`OTP: ${otpNumber}`);

    if (!otp || otp.includes(undefined) || otp.includes("")) {
      return form.setFields([
        {
          name: "otp",
          errors: ["OTP is invalid."]
        }
      ]);
    }

    axios.post(`${server_uri}/auth/authenticate`, { code: otpNumber }).then(req => {
      router.replace("/main");
    }).catch(err => { alert("check otp number") });


  };

  const [nickname, setNickname] = useState("name");



  useEffect(() => {    
    
    return () => {
    };

}, []);

  return (

    <div style={containerStyle}>
    <div style={loginFormStyle}>
      
    <main className="app">      
      <section className="card">                
        <Form form={form} onFinish={handleFinish}>           

          <Form.Item
            name="otp"
            className="center-error-message"
            rules={[{ validator: async () => Promise.resolve() }]}
          >
            <InputOTP autoFocus inputType="numeric" length={6} />
          </Form.Item>

          <Form.Item noStyle>
            <Button block htmlType="submit" type="primary">
              Submit
            </Button>
          </Form.Item>


        </Form>
      </section>
    </main>                  
    </div>
  </div>
  );

}
