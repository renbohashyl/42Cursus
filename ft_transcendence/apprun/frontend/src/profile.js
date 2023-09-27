import React from 'react';
import styled from 'styled-components';

const Section = styled.div`
  height: 600px;
  display: flex;
  align-items: center;
  justify-content: center;
`;

const Avator = styled(Section)`
  background-color: orange;
`;
  
const Level = styled(Section)`
  background-color: red;
`;

const Achievement = styled(Section)`
  background-color: blue;
`;

const MatchingHistory = styled(Section)`
  background-color: magenta;
`;

export default function ProfileContents() {
    return (
        <div>
            <Avator> 프로필 아바타 </Avator>
            <Level> 레벨 </Level>
            <Achievement> 업적 </Achievement>
            <MatchingHistory> 매칭 히스토리 </MatchingHistory>
        </div>
    );
}