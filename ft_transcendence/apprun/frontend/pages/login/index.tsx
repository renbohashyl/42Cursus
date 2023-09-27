import React from "react";
import { useRouter } from 'next/router';
import { clientConfig } from '../../oauth';

const oauthLink = `https://api.intra.42.fr/oauth/authorize?client_id=${clientConfig.client_id}&redirect_uri=${clientConfig.redirect_uri}&response_type=code`;

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
  maxHeight: '170px',
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
  const router = useRouter();

  const onClickLogin = () => {
    router.push(oauthLink);
  };

  return (
    <div style={containerStyle}>
      <div style={loginFormStyle}>
        <h2 style={headerTitleStyle}> Welcome to 42 Transcendence</h2>
        <h3 style={contentStyle}> The answer to life, the universe and everything</h3>
        <button style={buttonStyle} onClick={onClickLogin}>42 Sign in</button>
      </div>
    </div>
  );
}
