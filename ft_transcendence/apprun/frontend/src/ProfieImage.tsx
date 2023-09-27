import { UserOutlined   } from '@ant-design/icons';
import React from 'react';
import { Avatar, Space } from 'antd';

const ProfileImage: React.FC = (props) => (
    <Space direction="vertical" size={16}>
        <Avatar src={props.src} shape="square" size={128} icon={ <UserOutlined/> } />
    </Space>
);

export default ProfileImage;
